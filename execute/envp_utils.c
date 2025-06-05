/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:59:24 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:10:56 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_envp(t_shelldata *shell, t_env *env, int fr)
{
	t_env	*temp;
	int		count;
	int		i;

	temp = env;
	count = 0;
	i = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	env = temp;
	if (fr)
		free_2d_char(shell->envp);
	shell->envp = ft_calloc(count + 1, sizeof(char *));
	while (env)
	{
		shell->envp[i] = ft_threejoin(env->name, "=", env->value);
		env = env->next;
		i++;
	}
}
