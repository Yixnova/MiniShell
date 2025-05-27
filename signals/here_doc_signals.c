/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:44:10 by busseven          #+#    #+#             */
/*   Updated: 2025/05/27 09:39:07 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tokens_sigint_handler(int signum)
{
	long unsigned int	len;

	len = ft_strlen("> ") + ft_strlen(rl_line_buffer);
	if (ft_strlen(rl_line_buffer) == 0)
		len++;
	(void)signum;
	printf("\033[%luG", len);
	printf("^C\n");
	exit(130);
}

void	heredoc_sigint_handler(int signum)
{
	long unsigned int	len;

	len = ft_strlen("> ") + ft_strlen(rl_line_buffer);
	if (ft_strlen(rl_line_buffer) == 0)
		len++;
	(void)signum;
	printf("\033[%luG", len);
	printf("^C\n");
	exit(130);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_tokens_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = tokens_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
