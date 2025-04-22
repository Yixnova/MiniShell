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
void	make_cmd_heredocs(t_cmd *cmd)
{
	int	h;
	int	count;

	h = 0;
	count = 0;
	while (cmd->limiter_arr[count])
		count++;
	cmd->hd_arr = ft_calloc(count + 1, sizeof(int *));
	while (cmd)
	{
		while (count > 0)
		{
			cmd->hd_arr[h] = ft_calloc(2, sizeof(int));
			pipe(cmd->hd_arr[h]);
			open_here_document(cmd, h);
			count--;
			h++;
		}
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
	if(check_files_and_commands(shell, *(shell->cmds)))
		return ;
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