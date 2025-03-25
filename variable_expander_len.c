/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander_len.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:31:22 by busseven          #+#    #+#             */
/*   Updated: 2025/03/25 15:33:04 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_value_len(char	*name, t_env *env)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(name);
	while (env)
	{
		len2 = ft_strlen(env->name);
		if (!ft_strncmp(env->name, name, get_greater(len1, len2)))
			break ;
	}
	if(!env)
		return (0);
	else
		return (ft_strlen(env->value));
}
int		get_variable_len(char *s, int *i, int in_quotes, t_env *env)
{
	int	n;
	int	len;
	int	*name;

	(*i)++;
	n = i;
	len = 0;
	while (s[n])
	{
		if (in_quotes == 0 && (s[n] == 34 || s[n] == 39))
			break ;
		else if (in_quotes == 1 && s[n] == 34)
			break ;
		else if (is_space_character(s[n]))
			break ;
		n++;
	}
	name = ft_substr(s, *i, n - *i);
	*i = n;
	return (get_value_len(name, env));
}

int		get_substr_len(char const *s, unsigned int start, unsigned int end, t_env *env)
{
	int	len;
	int	i;
	int	in_quotes;
	int	type;

	len = 0;
	i = 0;
	while (s[i])
	{
		handle_quotes_removed(s, &i, &in_quotes, &type);
		if (in_quotes == 0 || (in_quotes == 1 && type == 34))
		{
			if (s[i] == '$')
				len += get_variable_len(s, &i, in_quotes, env);
		}
		else
			len++;
	}
}