/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:45:25 by busseven          #+#    #+#             */
/*   Updated: 2025/05/20 11:01:34 by busseven         ###   ########.fr       */
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

int	handle_pipe_and_quote(int *i, char **arr, int *type, char *input)
{
	if (!arr[*i + 1])
		return (1);
	while (arr[*i] && *type)
	{
		*type = check_unclosed_quotes(input);
		if (arr[*i] && arr[*i + 1] && is_in_str(arr[*i + 1], *type))
		{
			input = ft_myjoin(input, "\n", arr[*i + 1]);
			(*i)++;
		}
	}
	while (arr[*i] && ends_with_pipe(arr[*i]))
	{
		*type = check_unclosed_quotes(input);
		if (arr[*i] && arr[*i + 1])
			input = ft_myjoin(input, " ", arr[*i + 1]);
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
	char	*input;
	int		type;

	input = arr[*i];
	type = check_unclosed_quotes(input);
	while (arr[*i] && (ends_with_pipe(arr[*i]) || type))
	{
		if (handle_pipe_and_quote(i, arr, &type, input))
			break ;
	}
	shell->input = input;
}
