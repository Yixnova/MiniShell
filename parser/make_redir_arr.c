/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:24:35 by busseven          #+#    #+#             */
/*   Updated: 2025/04/10 15:26:55 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	copy_redir(t_cmd	*cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
		{
			
		}
	}
}

void	make_arg_array(t_cmd *cmd)
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