/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:50:15 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 12:59:22 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

int	set_env(t_env **env_list, const char *key, const char *value)
{
	t_env	*node;
	t_env	*new_node;

	node = find_env(*env_list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (-1);
	}
	else
	{
		new_node = create_env_variable(key, value);
		if (!new_node)
			return (-1);
		new_node->next = *env_list;
		*env_list = new_node;
	}
	return (0);
}

int	unset_env(t_env **env_list, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

void	unset_command(t_env **env, char **args)
{
	int	i;

	if (!args[1])
	{
		print_env_list(*env);
		return;
	}
	i = 1;
	while (args[i])
	{
		unset_env(env, args[i]);
		i++;
	}
}
