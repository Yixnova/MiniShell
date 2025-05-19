/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:58:49 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/19 18:26:00 by busseven         ###   ########.fr       */
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

void	sigint_handler(int signum)
{
	long unsigned int	len;

	len = ft_strlen(rl_line_buffer) + ft_strlen("myshell$ ");
	if(ft_strlen(rl_line_buffer) == 0)
		len++;
	g_signal_flag = 1;
	(void)signum;
	printf("\033[%luG", len);
	printf("%s\n", "^C");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int signum)
{
	(void)signum;
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
void	proc_sigquit_handler(int signum)
{
	(void)signum;
}

void	process_sigint_handler(int signum)
{
	g_signal_flag = 1;
	(void)signum;
	printf("%s\n", "^C");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	setup_process_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = process_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = proc_sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
void sigint_heredoc_handler(int signum)
{
	long unsigned int	len;

	len = ft_strlen("> ") + ft_strlen(rl_line_buffer);
	if(ft_strlen(rl_line_buffer) == 0)
		len++;
    (void)signum;
	printf("\033[%luG", len);
	printf("^C\n");
	exit(130);
}

void setup_child_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_heredoc_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
