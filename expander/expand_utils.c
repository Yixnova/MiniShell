/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:31:06 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/25 10:13:33 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

char	*expand_variable(t_expander *exp, t_shelldata *shell)
{
	t_env	*env_var;
	char	*var_name;
	char	*value = NULL;
	int		start;

	if (!exp->input[exp->index] ||
		(!(ft_isalpha(exp->input[exp->index]) || exp->input[exp->index] == '_' || exp->input[exp->index] == '?')))
	{
		value = ft_strdup("$");
		return (value);
	}
	if (exp->input[exp->index] == '?')
	{
		exp->index++;
		value = ft_itoa(shell->exit_status);
		return (value);
	}
	start = exp->index;
	if (ft_isalpha(exp->input[exp->index]) || exp->input[exp->index] == '_')
		exp->index++;
	while (ft_isalnum(exp->input[exp->index]) || exp->input[exp->index] == '_')
		exp->index++;
	var_name = ft_substr(exp->input, start, exp->index - start);
	if (var_name && var_name[0])
	{
		env_var = find_env(shell->env, var_name);
		if (env_var && env_var->value)
			value = ft_strdup(env_var->value);
		else
			value = ft_strdup("");
	}
	else
		value = ft_strdup("$");
	free(var_name);
	return (value);
}
