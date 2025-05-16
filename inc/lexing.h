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

typedef struct s_shelldata	t_shelldata;

char	**split_into_words(char *str);

int		assign_word_to_array(char **arr, char *str, int *i, int *n);
char	*copy_word(char *str, int *n);
void	skip_in_quotes(char *str, int *i, int type);
int		count_words(char *str);
void	handle_array_quotes(char *str, int *i, int *in_quotes, int *type);

void	unclosed_quotes(void);
int		tokenize_input(t_shelldata *data);
char	*rm_quotes(char *str, int opt);
char	*expand(char *token, void *shell, int opt);

int		add_tokens(t_shelldata *data);
int		continue_quoted_input(t_shelldata *data, int type);
int		check_unclosed_quotes(char *str);
void	make_input(int *i, t_shelldata *shell, char **arr);
int		handle_pipe(t_shelldata *data, int *i);
int		handle_quote(t_shelldata *data, int *i);

#endif
