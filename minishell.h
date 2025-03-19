/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/19 13:37:31 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef	struct s_shelldata
{
	char		*input;
	t_tokens 	*tokens;
};	t_shelldata

typedef	struct s_tokens
{
//token types = " ' < > >> << $? $characters=something
	int			type;
	t_tokens 	*tokens;
};	t_tokens

#endif