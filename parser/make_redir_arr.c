/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:24:35 by busseven          #+#    #+#             */
/*   Updated: 2025/04/11 10:06:13 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	make_redir_array(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
		{
			count++;
			while(is_redir(cmd->tokens[i]))
				i++;
		}
		i++;
	}
	cmd->redirs = ft_calloc(count + 1, sizeof(char *));
	copy_redir(cmd);
}