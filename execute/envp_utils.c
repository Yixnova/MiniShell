/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:59:24 by busseven          #+#    #+#             */
/*   Updated: 2025/05/20 16:29:51 by busseven         ###   ########.fr       */
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
	free_2d_char(shell->env->envp);
	shell->env->envp = ft_calloc(count + 1, sizeof(char *));
	while (temp)
	{
		shell->env->envp[i] = ft_myjoin(temp->name, "=", temp->value);
		temp = temp->next;
		i++;
	}
}
