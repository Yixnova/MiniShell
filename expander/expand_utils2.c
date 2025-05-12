/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:40:00 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/12 14:43:08 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

void	append_char(t_expander *exp, char c)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(exp->result);
	temp = ft_calloc(len + 2, sizeof(char));
	ft_strlcpy(temp, exp->result, len + 1);
	temp[len] = c;
	free(exp->result);
	exp->result = temp;
}

void	process_variable(t_expander *exp, t_shelldata *shell)
{
	char	*expanded;
	char	*temp;

	exp->index++;
	expanded = expand_variable(exp, shell);
	temp = ft_strjoin(exp->result, expanded);
	free(exp->result);
	free(expanded);
	exp->result = temp;
}

void	process_double_quotes(t_expander *exp, t_shelldata *shell)
{
	append_char(exp, '"');
	exp->index++;
	while (exp->input[exp->index] && exp->input[exp->index] != '"')
	{
		if (exp->input[exp->index] == '$')
			process_variable(exp, shell);
		else
			append_char(exp, exp->input[exp->index++]);
	}
	if (exp->input[exp->index] == '"')
	{
		append_char(exp, '"');
		exp->index++;
	}
}

void	process_single_quotes(t_expander *exp)
{
	int	start;

	append_char(exp, '\'');
	start = 0;
	exp->index++;
	start = exp->index;
	while (exp->input[exp->index] && exp->input[exp->index] != '\'')
		exp->index++;
	while (start < exp->index)
		append_char(exp, exp->input[start++]);
	if (exp->input[exp->index] == '\'')
	{
		append_char(exp, '\'');
		exp->index++;
	}
}
