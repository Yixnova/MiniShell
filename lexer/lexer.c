/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/05/22 13:13:17 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

int	wait_add_tokens(t_shelldata *data)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
		{
			g_signal_flag = 1;
			add_history(data->input);
			data->exit_status = 130;
			return (1);
		}
		else if (WEXITSTATUS(status) == 2)
			exit(2);
	}
	return (0);
}

int	parent_process(int *fd, t_shelldata *data)
{
	char	*buf;
	int		bytes;

	buf = ft_calloc(1, 42);
	bytes = 1;
	wait_add_tokens(data);
	close(fd[1]);
	while (bytes)
	{
		bytes = read(fd[0], buf, 42);
		if (!bytes)
			break ;
		data->input = ft_join(data->input, " ");
		data->input = ft_join(data->input, buf);
	}
	free(buf);
	close(fd[0]);
	free_2d_char(data->tokens);
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
	if (pid != 0)
		return (parent_process(fd, data));
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
	while (str && !is_all_spaces(str) && str[i])
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

int	tokenize_input(t_shelldata *data)
{
	char	*invalid_token;
	int		i;

	i = 0;
	if(is_all_spaces(data->input))
		return (1);
	if (check_unclosed_quotes(data->input))
		return (quote_error(data));
	data->tokens = split_into_words(data->input);
	if (!data->tokens)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return (1);
	}
	invalid_token = check_token_errors(data->tokens);
	if (invalid_token)
		return (syntax_error_invalid_token(invalid_token, data));
	i = 0;
	if (handle_pipe(data, &i))
		return (1);
	while (data->tokens[i])
		i++;
	i--;
	add_history(data->input);
	return (0);
}
