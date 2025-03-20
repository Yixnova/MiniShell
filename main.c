/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:53:08 by busseven          #+#    #+#             */
/*   Updated: 2025/03/20 14:44:41 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input_and_history(t_shelldata *shelldata)
{
	while (1)
	{
		setup_signals();
		shelldata->input = readline("prompt$ ");
		if (!shelldata->input)
		{
			free_shell_data(shelldata);
			exit(0);
		}
		if (!is_empty_line(shelldata->input))
		{
			add_history(shelldata->input);
			tokenize_input(shelldata);
		}
		free(shelldata->input);
	}
}

int	main(void)
{
	t_shelldata	*shelldata;

	shelldata = ft_calloc(1, sizeof(shelldata));
	setup_signals();
	handle_input_and_history(shelldata);
}
