/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:14:57 by busseven          #+#    #+#             */
/*   Updated: 2025/03/25 15:30:42 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

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
void	handle_quotes_removed(char *str, int *i, int *in_quotes, int *type)
{
	if (str[*i] == 39 || str[*i] == 34)
	{
		if (*in_quotes == 0)
		{
			*in_quotes = 1;
			*type = str[*i];
			*i += 1;
		}
		else if (*in_quotes == 1 && *type == str[*i])
		{
			*in_quotes = 0;
			*i += 1;
		}
	}
}

int		get_len(char const *s, unsigned int start, unsigned int end, t_env *env)
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
char	*ft_substr_env(char const *s, unsigned int start, unsigned int end, t_env *env)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = get_len(s, start, end, env);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	slen;

	slen = ft_strlen(s);
	i = 0;
	if (slen <= start)
		return (ft_strdup(""));
	if (slen < start + len)
		len = slen - start;
	sub_str = (char *) malloc (sizeof(char) * len + 1);
	if (!sub_str)
		return (NULL);
	while (i < len)
	{
		sub_str[i] = s[start];
		i++;
		start++;
	}
	sub_str[i] = 0;
	return (sub_str);
}
