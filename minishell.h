/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/19 12:58:18 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef	s_shelldata
{
	char		*input;
	t_tokens 	*tokens;
};	t_shelldata

typedef	s_tokens
{
//token types = " ' < > >> << $? $characters=something
	int			type;
	t_tokens 	*next;
};	t_tokens

# include "./ft_printf/ft_printf.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#endif