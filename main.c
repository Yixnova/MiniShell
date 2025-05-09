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

void	free_input_data(t_shelldata *shell)
{
	int	i;

	i = 0;
	free(shell->input);
	free_2d_char(shell->tokens);
	while(i < shell->cmd_count - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
	free(shell->pipes);
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

void	process_input(t_shelldata *shell)
{
	t_cmd	*temp;

	add_history(shell->input);
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
	while (1)
	{
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
		free_input_data(shell);
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
