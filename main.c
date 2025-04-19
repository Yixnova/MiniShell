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

void	init_parsedata(t_shelldata *shell)
{
	int		i;
	int		n;
	int		count;
	int		pipe_count;

	i = 0;
	count = 0;
	n = 0;
	while(shell->tokens[i])
	{
		if(ft_strlen(shell->tokens[i]) == 1 && shell->tokens[i][0] == '|')
			count++;
		i++;
	}
	shell->cmds = ft_calloc(count + 1, sizeof(t_cmd *));
	shell->cmd_count = count + 1;
	pipe_count = count;
	while(count + 1 > 0)
	{
		add_cmd(shell, ft_cmdnew());
		count--;
	}
	shell->pipes = ft_calloc(pipe_count, sizeof(int *));
	while(pipe_count > 0)
	{
		shell->pipes[n] = ft_calloc(2, sizeof(int));
		pipe(shell->pipes[n]);
		pipe_count--;
		n++;
	}
}
void	free_shell_data(t_shelldata *data)
{
	if (data)
	{
		free(data->input);
		free_token_arr(data->tokens);
		free_env_list(data->env);
		free(data);
	}
}

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
int	find_command_path(t_cmd *cmd, t_shelldata *shell)
{
	if (check_builtin_and_path(cmd, shell))
		return (1);
	if (search_in_paths(cmd, shell))
		return (1);
	return(0);
}

void	check_files_and_commands(t_shelldata *data, t_cmd *cmd)
{
	while(cmd)
	{
		pick_pipes(cmd);
		open_files(cmd);
		pick_file_descriptors(cmd);
		if(!find_command_path(cmd, data))
			cmd->invalid = 1;
		cmd = cmd->next;
	}
}
void	process_input(t_shelldata *shell)
{
	add_history(shell->input);
	if(tokenize_input(shell))
		return ;
	init_parsedata(shell);
	edit_cmds_arr(shell, *(shell->cmds), 0, 0);
	open_all_heredoc(*(shell->cmds));
	check_files_and_commands(shell, *(shell->cmds));
	start_processes(shell, shell->cmds);
}

void	handle_input_and_history(t_shelldata *shell)
{
	while (1)
	{
		if (g_signal_flag)
		{
			g_signal_flag = 0;
			continue ;
		}
		shell->input = readline("myshell$ ");
		if (!shell->input)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (shell->input[0] != '\0')
		{
			process_input(shell);
		}
		free(shell->input);
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