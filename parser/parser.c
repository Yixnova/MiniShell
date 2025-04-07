/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/07 18:53:44 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		is_input(char	*str)
{
	if(!ft_strncmp(str, "<", ft_strlen(str)))
		return (1);
	else if(!ft_strncmp(str, "<<", ft_strlen(str)))
		return (2);
	return (0);
}
int		*ft_intjoin(int	*arr, int n)
{
	int	i;
	int	*new;

	i = 0;
	if(!arr)
		arr = ft_calloc(1, sizeof(int));
	while(arr[i])
		i++;
	new = ft_calloc(i + 1, sizeof(int));
	i = 0;
	while(arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = n;
	free(arr);
	return(new);
}

t_cmd	*make_token_list(t_shelldata	*shell)
{
	int	i;
	int	*arg_indexes;
	t_cmd	*temp;
	t_cmd	*first;

	i = 0;
	temp = ft_calloc(1, sizeof(t_cmd));
	first = temp;
	while(shell->token_arr[i])
	{
		if(ft_strlen(str) == 1 && str[0] == '|')
			temp->next = add_pipe(*i, shell->token_arr);
		else if(!ft_strncmp(str, "<", ft_strlen(str)))
			temp->next = add_input(*i, shell->token_arr);
		else if(!ft_strncmp(str, "<<", ft_strlen(str)))
			temp->next	= add_heredoc(*i, shell->token_arr);
		else if(is_output(str) != 0)
			temp->next = add_output(*i, shell->token_arr, is_output(str));
		else
		{
			arg_indexes = ft_intjoin(arg_indexes, i);
			i++;
		}
		temp = temp->next;
	}
}
