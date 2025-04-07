/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:04:14 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/07 10:53:17 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

static void	append_char(t_expander *exp, char c)
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

static void	process_variable(t_expander *exp, t_shelldata *shell)
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

static void	process_double_quotes(t_expander *exp, t_shelldata *shell)
{
	while (exp->input[exp->index])
	{
		if (exp->input[exp->index] == '$')
			process_variable(exp, shell);
		else
			append_char(exp, exp->input[exp->index++]);
	}
	if (exp->input[exp->index] == '"')
		exp->index++;
}

static void	process_single_quotes(t_expander *exp)
{
	char	*expanded;
	char	*temp;
	int		start;

	start = exp->index;
	while (exp->input[exp->index] && exp->input[exp->index] != '\'')
		exp->index++;
	expanded = ft_substr(exp->input, start, exp->index - start + 1);
	temp = ft_strjoin(exp->result, expanded);
	free(exp->result);
	free(expanded);
	exp->result = temp;
	if (exp->input[exp->index] == '\'')
		exp->index++;
}

char	*expand_string(const char *str, t_shelldata *shell)
{
	t_expander	exp;

	exp.input = str;
	exp.result = ft_calloc(1, sizeof(char));
	exp.index = 0;
	while (exp.input[exp.index])
	{
		if (exp.input[exp.index] == '$')
			process_variable(&exp, shell);
		else if (exp.input[exp.index] == '"')
			process_double_quotes(&exp, shell);
		else if (exp.input[exp.index] == '\'')
			process_single_quotes(&exp);
		else
			append_char(&exp, exp.input[exp.index++]);
	}
	return (exp.result);
}
