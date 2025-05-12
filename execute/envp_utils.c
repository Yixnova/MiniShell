/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:59:24 by busseven          #+#    #+#             */
/*   Updated: 2025/05/12 14:24:59 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_envp(t_shelldata *shell, t_env *env)
{
	t_env	*temp;
	int		count;
	int		i;

	temp = env;
	count = 0;
	i = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	temp = env;
	shell->env->envp = ft_calloc(count + 1, sizeof(char *));
	while (temp)
	{
		shell->env->envp[i] = ft_myjoin(temp->name, "=", temp->value);
		temp = temp->next;
		i++;
	}
}
