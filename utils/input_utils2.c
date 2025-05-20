/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:45:25 by busseven          #+#    #+#             */
/*   Updated: 2025/05/20 15:50:21 by busseven         ###   ########.fr       */
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

int	handle_pipe_and_quote(int *i, char **arr, int *type, t_shelldata *shell)
{
	int	k;

	k = *i + 1;
	while(arr[k] && arr[k][0] == '\0')
		k++;
	if (!arr[k])
		return (1);
	while (arr[*i] && *type)
	{
		*type = check_unclosed_quotes(shell->input);
		if (arr[*i] && arr[k] && is_in_str(arr[k], *type))
		{
			shell->input = ft_join(shell->input, "\n");
			shell->input = ft_join(shell->input, arr[k]);
			(*i)++;
		}
	}
	while (arr[*i] && ends_with_pipe(arr[*i]))
	{
		*type = check_unclosed_quotes(shell->input);
		if (arr[*i] && arr[*i + 1])
		{
			shell->input = ft_join(shell->input, " ");
			shell->input = ft_join(shell->input, arr[k]);
		}
		(*i)++;
	}
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
	int		type;

	shell->input = arr[*i];
	type = check_unclosed_quotes(shell->input);
	while (arr[*i] && (ends_with_pipe(arr[*i]) || type))
	{
		if (handle_pipe_and_quote(i, arr, &type, shell))
			break ;
	}
}
