/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:11:42 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/21 18:08:22 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

char	*expand_variable(t_expander *exp, t_shelldata *shell)
{
	t_env	*env_var;
	char	*var_name;
	char	*value = NULL;
	int		start;

	// Special case: just '$' at end or not followed by valid var/param
	if (!exp->input[exp->index] ||
		(!(ft_isalpha(exp->input[exp->index]) || exp->input[exp->index] == '_' || exp->input[exp->index] == '?')))
	{
		// Output literal '$'
		value = ft_strdup("$");
		return (value);
	}
	// Special parameter $?
	if (exp->input[exp->index] == '?')
	{
		exp->index++;
		value = ft_itoa(shell->exit_status);
		return (value);
	}
	// Parse variable name: [a-zA-Z_][a-zA-Z0-9_]*
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
