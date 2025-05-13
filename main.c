/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:53:08 by busseven          #+#             */
/*   Updated: 2025/04/06 17:36:58 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

char	*check_token_errors(char **tokens)
{
	int	i;

	i = 0;
	while(tokens[i])
	{
		if(is_redir(tokens[i]))
		{
			if(ft_strlen(tokens[i]) > 2)
				return(tokens[i]);
			else if(ft_strlen(tokens[i]) == 2 && tokens[i][0] != tokens[i][1])
				return(tokens[i]);
			else if(!tokens[i + 1] || is_redir(tokens[i + 1]) || is_pipe(tokens[i + 1]))
				return(tokens[i]);
		}
		if(is_pipe(tokens[i]))
		{
			if(i == 0 || is_redir(tokens[i - 1]))
				return(tokens[i]);
		}
		i++;
	}
	return (NULL);
}
int		ends_with_pipe(char *str)
{
	int	pipe;
	int	i;

	i = 0;
	pipe = 0;
	while(str[i])
	{
		if(str[i] == '|')
		{
			pipe = 1;
			break ;
		}
		i++;
	}
	if(pipe == 0)
		return(0);
	i++;
	if(str[i] == '\0' || is_all_spaces(str + i))
		return (1);
	return (0);
}
void	make_input(int *i, t_shelldata *shell, char **arr)
{
	char	*input;

	input = arr[*i];
	while(arr[*i] && ends_with_pipe(arr[*i]))
	{
		if(arr[*i] && arr[*i + 1])
		{
			input = ft_myjoin(input, " ", arr[*i + 1]);
		}
		(*i)++;
	}
	shell->input = input;
}

void	free_input_data(t_shelldata *shell)
{
	int	i;

	i = 0;
	free_2d_char(shell->tokens);
	while(i < shell->cmd_count - 1)
	{
		if(shell->pipes[i])
			free(shell->pipes[i]);
		i++;
	}
	if(shell->cmd_count > 1)
		free(shell->pipes);
	if(shell->pids)
		free(shell->pids);
	while(shell->cmds && *(shell->cmds))
	{
		i = 0;
		while((*(shell->cmds))->has_hd && (*(shell->cmds))->limiter_arr[i])
		{
			free((*(shell->cmds))->hd_arr[i]);
			i++;
		}
		free_2d_char((*(shell->cmds))->tokens);
		free_2d_char((*(shell->cmds))->args);
		free_2d_char((*(shell->cmds))->redirs);
		if((*(shell->cmds))->has_hd)
			free_2d_char((*(shell->cmds))->limiter_arr);
		free((*(shell->cmds))->hd_parsedollar);
		free((*(shell->cmds))->file_descs);
		free((*(shell->cmds))->path);
		*(shell->cmds) = (*(shell->cmds))->next;
	}
}

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	process_input(t_shelldata *shell)
{
	t_cmd	*temp;

	if (tokenize_input(shell))
		return ;
	init_parsedata(shell);
	if(edit_cmds_arr(shell, *(shell->cmds), 0, 0))
		return ;
	temp = *(shell->cmds);
	while (temp)
	{
		if (temp->has_hd)
			make_cmd_heredocs(temp, shell);
		temp = temp->next;
	}
	if (*(shell->cmds) && (*(shell->cmds))->args
		&& (*(shell->cmds))->next == NULL
		&& !ft_strcmp((*(shell->cmds))->args[0], "exit"))
	{
		exit_command((*(shell->cmds))->args, shell);
		return ;
	}
	start_processes(shell, shell->cmds);
}

void	handle_input_and_history(t_shelldata *shell)
{
	char	*read_line;
	char	**input_arr;
	int		i;

	i = 0;
	while (1)
	{
		read_line = readline("myshell$ ");
		if (!read_line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		input_arr = ft_split(read_line, '\n');
		i = 0;
		while(input_arr && input_arr[i])
		{
			make_input(&i, shell, input_arr);
			if (!shell->input)
			{
				ft_putendl_fd("exit", 1);
				break ;
			}
			add_history(shell->input);
			if(check_unclosed_quotes(shell))
			{
				ft_putstr_fd("Syntax error: unclosed quotes\n", 2);
				shell->exit_status = 2;
				break ;
			}
			if (shell->input[0] != '\0')
			{
				process_input(shell);
			}
			if(!input_arr || !input_arr[i])
				break ;
			i++;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shelldata	*shell;

	(void)argc;
	(void)argv;
	errno = 0;
	shell = ft_calloc(1, sizeof(t_shelldata));
	if (!shell)
	{
		ft_putendl_fd("Malloc error", 2);
		return (EXIT_FAILURE);
	}
	shell->env = build_env_list(envp);
	if (!shell->env)
	{
		ft_putendl_fd("Error", 2);
		return (EXIT_FAILURE);
	}
	disable_echoctl();
	setup_signals();
	handle_input_and_history(shell);
	return (EXIT_SUCCESS);
}
