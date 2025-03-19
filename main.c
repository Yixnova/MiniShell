/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:53:08 by busseven          #+#    #+#             */
/*   Updated: 2025/03/19 12:50:08 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	is_space_character(char c)
{
	return(c == ' ' || (c >= 9 && c <= 13));
}
int	is_all_spaces(char *line)
{
	int	i;
	i = 0;
	
	while(line[i])
	{
		if(!is_space_character(line[i]))
			return (1);
		i++;
	}
	return (0);
}
int is_empty_line(char *line)
{
	return(!line || line[0] == '\0' || is_all_spaces(line));
}

void	handle_input_and_history(t_shelldata *shelldata)
{
	while(1)
	{
		shelldata->input = readline("prompt$ ");
		if(!is_empty_line(shelldata->input))
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