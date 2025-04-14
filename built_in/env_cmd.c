/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:48:33 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/14 09:40:53 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

t_env	*build_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = -1;
	while (envp[++i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
			return (NULL);
		if (!head)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}
	head->envp = envp;
	return (head);
}

t_env	*find_env(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->name, key, ft_strlen(key) + 1) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

t_env	*create_env_variable(const char *key, const char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->name || !new_node->value)
	{
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	env_command(t_env *env, char **args)
{
	(void)args;
	print_env_list(env);
}
