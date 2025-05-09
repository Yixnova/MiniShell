/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:50:15 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/09 14:40:39 by busseven         ###   ########.fr       */
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
		if (ft_strcmp(current->name, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

int	unset_command(t_env **env, char **args)
{
	int		i;
	char	*equal;
	size_t	key_len;
	char	*key;

	i = 1;
	if (!args[1])
		return (0);
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			key_len = equal - args[i];
			key = ft_strndup(args[i], key_len);
			unset_env(env, key);
			free(key);
		}
		else
			unset_env(env, args[i]);
		i++;
	}
	return (0);
}
