/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/08 12:09:13 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		*ft_intjoin(int	*arr, int n)
{
	int	i;
	int	*new;

	i = 0;
	if(!arr)
		arr = ft_calloc(1, sizeof(int));
	while(arr[i])
		i++;
	new = ft_calloc(i + 1, sizeof(int));
	i = 0;
	while(arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = n;
	free(arr);
	return(new);
}

void	parser(t_shelldata *shell)
{
	int	pid;
	int	status;

	pid = fork();
	if(pid == 0)
	{
		//burda dosyaları openlayıp sonra execute fonksiyonu çalışacak ve bi liste oluşturup free atacak
	}
	else
	{
		//recursive olarak bişiler gönderip tekrar çalışıcak parser()
	}
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
	{
		//child'ın exit statusunu çeker
		shell->exit = WEXITSTATUS(status);
	}
}