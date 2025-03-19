/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:53:08 by busseven          #+#    #+#             */
/*   Updated: 2025/03/19 17:58:16 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input_and_history(t_shelldata *shelldata)
{
	while (1)
	{
		shelldata->input = readline("prompt$ ");
		if (!is_empty_line(shelldata->input))
			add_history(shelldata->input);
		free(shelldata->input);
	}
}

int	main()
{
	t_shelldata	*shelldata;

	shelldata = ft_calloc(1, sizeof(shelldata));
	handle_input_and_history(shelldata);
}
