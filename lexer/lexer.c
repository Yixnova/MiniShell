/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 18:44:50 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

int	quote_error(t_shelldata *data)
{
	ft_putstr_fd("Syntax error: Unclosed quote\n", 2);
	data->exit_status = 2;
	add_history(data->input);
	return (1);
}
int	syntax_error_invalid_token(char *token, t_shelldata *data)
{
	ft_putstr_fd("Syntax error: invalid use of token: ", 2);
	ft_putstr_fd(token, 2);
	ft_putchar_fd('\n', 2);
	data->exit_status = 2;
	add_history(data->input);
	return (1);
}
int	parent_process(int *fd, t_shelldata *data)
{
	char	*buf;
	int		bytes;
	int		status;

	buf = ft_calloc(1, 42);
	bytes = 1;
	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFEXITED(status))
	{
		if(WEXITSTATUS(status) == 130)
		{
			g_signal_flag = 1;
			add_history(data->input);
			return(1);	
		}
		else if(WEXITSTATUS(status) == 2)
			exit(2);
	}
	close(fd[1]);
	while(bytes)
	{
		bytes = read(fd[0], buf, 42);
		if(!bytes)
			break ;
		data->input = ft_myjoin(data->input, " ", buf);
	}
	free(buf);
	close(fd[0]);
	printf("input: %s\n", data->input);
	data->tokens = split_into_words(data->input);
	return (0);	
}

int	add_tokens(t_shelldata *data)
{
	char	*line;
	int		pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if(pid != 0)
		return(parent_process(fd, data));
	else
	{
		setup_heredoc_signals();
		line = readline("> ");
		close(fd[0]);
		if (!line)
		{
			syntax_error_eof();
			exit(2);
		}
		write(fd[1], line, ft_strlen(line));
		close(fd[1]);
		free(line);
		exit (0);
	}
}

int	check_unclosed_quotes(char *str)
{
	int	type;
	int	in_quotes;
	int	i;

	i = 0;
	type = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (in_quotes == 0)
			{
				type = str[i];
				in_quotes = 1;
			}
			else if (in_quotes == 1 && str[i] == type)
				in_quotes = 0;
		}
		i++;
	}
	if (in_quotes == 1)
		return (type);
	else
		return (0);
}

int	continue_quoted_input(t_shelldata *data, int type)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: ", 11);
			write(2, "unexpected EOF while looking for matching \"\'\n", 46);
			syntax_error_eof();
			return (1);
		}
		data->input = ft_myjoin(data->input, "\n", line);
		if (is_in_str(line, type))
		{
			free(line);
			break ;
		}
		free(line);
	}
	free_2d_char(data->tokens);
	data->tokens = split_into_words(data->input);
	return (0);
}

int	tokenize_input(t_shelldata *data)
{
	char	*invalid_token;
	int		i;

	i = 0;
	data->tokens = split_into_words(data->input);
	if (!data->tokens)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return (1);
	}
	invalid_token = check_token_errors(data->tokens);
	if(invalid_token)
		return(syntax_error_invalid_token(invalid_token, data));
	i = 0;
	if(handle_pipe(data, &i))
		return (1);
	while(data->tokens[i])
		i++;
	i--;
	if(check_unclosed_quotes(data->tokens[i]))
		return(quote_error(data));
	add_history(data->input);
	return (0);
}
