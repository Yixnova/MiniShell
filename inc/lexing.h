/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:12:11 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 20:19:31 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

char	**split_into_words(char *str);
void	unclosed_quotes();
void	tokenize_input(t_shelldata	*data);
char	*remove_quotes(char *str);

# endif
