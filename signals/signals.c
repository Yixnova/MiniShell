/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:58:49 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/09 13:55:46 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal_flag = 0;

#ifdef __APPLE__
void	rl_replace_line(const char *text, int clear_undo)
{

	(void)clear_undo;
	rl_delete_text(0, rl_end);
	rl_insert_text(text);
}
#endif

void	cleanup_resources(void)
{
	rl_clear_history();
}

void	sigint_handler(int signum)
{
	(void)signum;
	g_signal_flag = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
