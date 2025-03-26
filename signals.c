/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:58:49 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 20:04:04 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

#ifdef __APPLE__
void	rl_replace_line(const char *text, int clear_undo)
{
	// clear_undo is ignored
	(void)clear_undo;
	rl_delete_text(0, rl_end);
	rl_insert_text(text);
}
#endif

// ctrl-C displays a new prompt on a new line; ctrl-\ does nothing as SIGQUIT is ignored
void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1); // use write to flush output immediately
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	// Set up handlers: ctrl-C via SIGINT and ignore ctrl-\ via SIGQUIT
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
