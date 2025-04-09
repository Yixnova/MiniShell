/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:12:11 by yigsahin          #+#             */
/*   Updated: 2025/04/09 13:20:05 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

typedef struct s_shelldata t_shelldata;

char	**split_into_words(char *str);

int		assign_word_to_array(char **arr, char *str, int *i, int *n);
char	*copy_word(char *str, int *n);
void	skip_in_quotes(char *str, int *i, int type);
int		count_words(char *str);
void	handle_array_quotes(char *str, int *i, int *in_quotes, int *type);

void	unclosed_quotes(void);
void	tokenize_input(t_shelldata *data);
char	*remove_quotes(char *str);
void	free_token_arr(char **token_arr);

#endif
