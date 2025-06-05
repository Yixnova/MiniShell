/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:53:34 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:12:25 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*delete(char **s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(s[i]);
		i++;
	}
	free (s);
	return (NULL);
}

static int	counter(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*filler(const char *s, char c)
{
	int			lc;
	int			i;
	char		*string;
	const char	*copied;

	i = 0;
	lc = 0;
	copied = s;
	while (*s != c && *s)
	{
		lc++;
		s++;
	}
	string = (char *) malloc (sizeof(char) * (lc + 1));
	if (!string)
		return (NULL);
	while (i < lc)
	{
		string[i++] = *copied++;
	}
	string[i] = 0;
	return (string);
}

char	**ft_split(char const *s, char c)
{
	char		**strings;
	int			i;
	int			wc;

	i = 0;
	wc = counter(s, c);
	strings = (char **) malloc (sizeof(char *) * (wc + 1));
	if (!strings)
		return (NULL);
	while (i < wc)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			strings[i] = filler(s, c);
			if (!strings[i])
				return (delete (strings, i));
			while (*s && *s != c)
				s++;
		}
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
