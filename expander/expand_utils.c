/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:11:42 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/06 17:39:55 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

char	*expand_variable(t_expander *exp, t_shelldata *shell)
{
	t_env	*env_var;
	char	*var_name;
	char	*value;
	int		start;

	start = exp->index;
	while (exp->input[exp->index] && exp->input[exp->index] != ' '
		&& exp->input[exp->index] != '$' && exp->input[exp->index] != '"'
		&& exp->input[exp->index] != '\'')
	{
		exp->index++;
	}
	var_name = ft_substr(exp->input, start, exp->index - start);
	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(shell->exit_status);
	else
	{
		env_var = find_env(shell->env, var_name);
		if (env_var)
			value = ft_strdup(env_var->value);
		else
			value = ft_strdup("");
	}
	free(var_name);
	return (value);
}
