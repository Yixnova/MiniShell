/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:04:36 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/12 13:39:15 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../inc/minishell.h"

typedef struct s_shelldata	t_shelldata;

typedef struct s_expander
{
	const char	*input;
	char		*result;
	int			index;
}	t_expander;

char	*expand(char *str, t_shelldata *shell);
char	*expand_variable(t_expander *exp, t_shelldata *shell);

#endif
