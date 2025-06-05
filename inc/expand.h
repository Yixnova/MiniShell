/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:04:36 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:21 by yigsahin         ###   ########.fr       */
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

char	*expand_str(char *str, t_shelldata *shell, int opt);
char	*expand_variable(t_expander *exp, t_shelldata *shell);
void	process_variable(t_expander *exp, t_shelldata *shell);
void	process_double_quotes(t_expander *exp, t_shelldata *shell);
void	process_single_quotes(t_expander *exp);
void	append_char(t_expander *exp, char c);

#endif
