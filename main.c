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

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	return (new);
}
void	add_cmd(t_shelldata *shell, t_cmd *new)
{
	t_cmd	*temp;

	if (!*(shell->cmds))
	{
		*(shell->cmds) = new;
		return ;
	}
	temp = *(shell->cmds);
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
	new->prev = temp;
}

void	init_parsedata(t_shelldata *shell)
{
	int		i;

	i = 0;
	shell->cmds = ft_calloc(1, sizeof(t_cmd **));
	while(shell->token_arr[i])
	{
		if(ft_strncmp(shell->token_arr[i], "|", ft_strlen(shell->token_arr[i])))
		{
			add_cmd(shell, ft_cmdnew());
		}
		i++;
	}
}
void	free_shell_data(t_shelldata *data)
{
	if (data)
	{
		free(data->input);
		free_token_arr(data->token_arr);
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
			execute_command(shell);
		}
		free(shell->input);
		shell->input = NULL;
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
