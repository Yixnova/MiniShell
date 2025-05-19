/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:11:03 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 17:27:19 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

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
			if(add_tokens(data))
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

int	handle_quote(t_shelldata *data, int *i)
{
	char	*invalid_token;

	while(data->tokens[*i] && check_unclosed_quotes(data->tokens[*i]))
	{
		*i = 0;
		invalid_token = check_token_errors(data->tokens);
		if(invalid_token)
			return(syntax_error_invalid_token(invalid_token, data));
		while(data->tokens[*i])
			(*i)++;
		(*i)--;
		if(data->tokens[*i] && check_unclosed_quotes(data->tokens[*i]))
		{
			if(continue_quoted_input(data, check_unclosed_quotes(data->tokens[*i])))
				return(1);
		}
	}
	return (0);
}