/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:04:14 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/16 11:35:27 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

char	*expand_str(char *str, t_shelldata *shell, int opt)
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
	if(opt == 1)
		free(str);
	return (exp.result);
}

char	*expand(char *token, void *shell, int opt)
{
	return (expand_str(token, (t_shelldata *)shell, opt));
}
