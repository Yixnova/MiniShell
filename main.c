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

	g_signal_flag = 0;
	if (tokenize_input(shell))
		return ;
	init_parsedata(shell);
	if (edit_cmds_arr(shell, *(shell->cmds), 0, 0))
		return ;
	temp = *(shell->cmds);
	while (temp)
	{
		if (temp->has_hd)
			make_cmd_heredocs(temp, shell);
		if (g_signal_flag == 1)
			return ;
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

void	iterate_input_arr(char **input_arr, t_shelldata *shell)
{
	int	i;

	i = 0;
	while (input_arr && input_arr[i])
	{
		make_input(&i, shell, input_arr);
		if (!shell->input)
		{
			free_shell(shell);
			ft_putendl_fd("exit", 1);
			exit (0);
		}
		if (shell->input[0] != '\0')
			process_input(shell);
		if (!input_arr || !input_arr[i])
			return ;
		i++;
		free_input_data(shell);
	}
}

void	handle_input_and_history(t_shelldata *shell)
{
	while (1)
	{
		shell->read_line = readline("myshell$ ");
		if (!shell->read_line)
		{
			ft_putendl_fd("exit", 1);
			free(shell->read_line);
			free_2d_char(shell->env->envp);
			free_env_list(shell->env);
			free(shell);
			break ;
		}
		shell->input_arr = ft_split(shell->read_line, '\n');
		iterate_input_arr(shell->input_arr, shell);
		free_2d_char(shell->input_arr);
		free(shell->read_line);
		shell->iteration_count++;
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
	set_envp(shell, shell->env, 0);
	shell->iteration_count = 0;
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
