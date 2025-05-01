/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:31:06 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/01 13:26:49 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expand.h"

char	*get_env_value(t_shelldata *shell, char *var_name)
{
	t_env	*env_var;

	env_var = find_env(shell->env, var_name);
	if (env_var && env_var->value)
		return (ft_strdup(env_var->value));
	return (ft_strdup(""));
}

static int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

static char	*handle_special_cases(t_expander *exp, t_shelldata *shell)
{
	if (!exp->input[exp->index] || !is_valid_var_start(exp->input[exp->index]))
		return (ft_strdup("$"));
	if (exp->input[exp->index] == '?')
	{
		exp->index++;
		return (ft_itoa(shell->exit_status));
	}
	return (NULL);
}

static char	*parse_and_get_value(t_expander *exp, t_shelldata *shell)
{
	char	*var_name;
	char	*value;
	int		start;

	start = exp->index;
	if (ft_isalpha(exp->input[exp->index]) || exp->input[exp->index] == '_')
		exp->index++;
	while (ft_isalnum(exp->input[exp->index]) || exp->input[exp->index] == '_')
		exp->index++;
	var_name = ft_substr(exp->input, start, exp->index - start);
	if (var_name && var_name[0])
		value = get_env_value(shell, var_name);
	else
		value = ft_strdup("$");
	free(var_name);
	return (value);
}

char	*expand_variable(t_expander *exp, t_shelldata *shell)
{
	char	*value;

	value = handle_special_cases(exp, shell);
	if (value)
		return (value);
	value = parse_and_get_value(exp, shell);
	return (value);
}
