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
	int		count;

	i = 0;
	count = 0;
	while(shell->tokens[i])
	{
		if(ft_strlen(shell->tokens[i]) == 1 && shell->tokens[i][0] == '|')
			count++;
		i++;
	}
	shell->cmds = ft_calloc(count + 1, sizeof(t_cmd *));
	while(count + 1 > 0)
	{
		add_cmd(shell, ft_cmdnew());
		count--;
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
			add_history(shell->input);
			tokenize_input(shell);
			init_parsedata(shell);
			edit_cmds_arr(shell, *(shell->cmds), 0, 0);
			open_all_heredoc(*(shell->cmds));
			execute_command(shell, shell);
		}
		free(shell->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shelldata	*shell;

	(void)argc;
	(void)argv;
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
