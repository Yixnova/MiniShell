/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:45:25 by busseven          #+#    #+#             */
/*   Updated: 2025/05/21 16:28:53 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

int	ends_with_pipe(char *str)
{
	int	pipe;
	int	i;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			pipe = 1;
			break ;
		}
		i++;
	}
	if (pipe == 0)
		return (0);
	i++;
	if (str[i] == '\0' || is_all_spaces(str + i))
		return (1);
	return (0);
}

int	is_pipe_with_newline(char *str)
{
	if (!ft_strncmp(str, "|\n", ft_strlen(str)))
		return (1);
	return (0);
}

char	*check_token_errors(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redir(tokens[i]))
		{
			if (ft_strlen(tokens[i]) > 2)
				return (tokens[i]);
			else if (ft_strlen(tokens[i]) == 2 && tokens[i][0] != tokens[i][1])
				return (tokens[i]);
			else if (!tokens[i + 1] || is_redir(tokens[i + 1])
				|| is_pipe(tokens[i + 1]))
				return (tokens[i]);
		}
		if (is_pipe(tokens[i]) || is_pipe_with_newline(tokens[i]))
		{
			if (i == 0 || is_redir(tokens[i - 1])
				|| is_pipe(tokens[i - 1])
				|| is_pipe_with_newline(tokens[i - 1]))
				return (tokens[i]);
		}
		i++;
	}
	return (NULL);
}

void	make_input(int *i, t_shelldata *shell, char **arr)
{
	shell->input = ft_strdup(arr[*i]);
}
