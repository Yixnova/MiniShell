/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:20:11 by yigsahin          #+#    #+#             */
/*   Updated: 2024/10/29 15:31:23 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!(*lst) || !del || !lst)
		return ;
	tmp = (*lst)->next;
	while ((*lst))
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		(*lst) = tmp;
	}
}
