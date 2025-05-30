/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:11:03 by busseven          #+#    #+#             */
/*   Updated: 2025/05/30 14:01:22 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_myjoin_free(char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	free(s1);
	return (result);
}

int	handle_pipe(t_shelldata *data, int *i)
{
	char	*invalid_token;

	while (data->tokens[*i])
	{
		*i = 0;
		invalid_token = check_token_errors(data->tokens);
		if (invalid_token)
			return (syntax_error_invalid_token(invalid_token, data));
		while (data->tokens[*i])
			(*i)++;
		(*i)--;
		if (data->tokens[*i] && is_pipe(data->tokens[*i]))
		{
			if (add_tokens(data))
			{
				setup_signals();
				return (1);
			}
			setup_signals();
		}
		else
			return (0);
	}
	return (0);
}
