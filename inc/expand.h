/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:04:36 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/09 13:19:57 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../inc/minishell.h"

typedef struct s_expander
{
	const char	*input;
	char		*result;
	int			index;
}	t_expander;

char	*expand_string(char *str, t_shelldata *shell);
char	*expand_variable(t_expander *exp, t_shelldata *shell);

#endif
