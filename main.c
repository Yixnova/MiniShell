/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:53:08 by busseven          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/21 18:15:41 by busseven         ###   ########.fr       */
=======
/*   Updated: 2025/03/26 13:14:12 by yigsahin         ###   ########.fr       */
>>>>>>> f50185ad19117edef407fa763b825456f7c26f23
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	free_shell_data(t_shelldata *data)
{
	if (data)
	{
		free(data->input);
		free(data);
	}
	free_env_list(data->env);
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
		if (!is_empty_line(shelldata->input))
		{
			add_history(shelldata->input);
			tokenize_input(shelldata);
		}
		free(shelldata->input);
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
	handle_input_and_history(shell);
	free_shell_data(shell);
	return (EXIT_SUCCESS);
}
