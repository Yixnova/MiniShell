/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:39:47 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/02 16:01:01 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

t_env	*create_env_node(const char *env_entry)
{
	t_env		*node;
	const char	*equal_sign;
	size_t		key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = strchr(env_entry, '=');
	if (equal_sign)
	{
		key_len = equal_sign - env_entry;
		node->name = ft_strndup(env_entry, key_len);
		node->value = strdup(equal_sign + 1);
	}
	else
	{
		node->name = ft_strdup(env_entry);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

void	print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
