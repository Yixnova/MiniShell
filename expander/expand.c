/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:04:14 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/02 16:06:13 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

char	*expand_str(char *str, t_shelldata *shell)
{
	t_expander	exp;

	exp.input = str;
	exp.result = ft_calloc(1, sizeof(char));
	exp.index = 0;
	while (exp.input && exp.input[exp.index])
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

char	*expand(char *token, void *shell)
{
	return (expand_str(token, (t_shelldata *)shell));
}
