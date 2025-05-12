/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:28:17 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/12 14:43:28 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/history.h"

static char	*get_history_path(void)
{
	char	*home;
	char	*path;
	size_t	len;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	len = strlen(home) + 1 + strlen(HISTORY_FILE) + 1;
	path = malloc(len);
	if (!path)
		return (NULL);
	snprintf(path, len, "%s/%s", home, HISTORY_FILE);
	return (path);
}

void	load_history_from_file(void)
{
	char	*path;

	path = get_history_path();
	if (!path)
		return ;
	read_history(path);
	free(path);
}

void	append_history_to_file(const char *line)
{
	char	*path;
	int		fd;

	path = get_history_path();
	if (!path)
		return ;
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		free(path);
		return ;
	}
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
	close(fd);
	free(path);
}

void	save_history_on_exit(void)
{
	char	*path;

	path = get_history_path();
	if (!path)
		return ;
	write_history(path);
	free(path);
}
