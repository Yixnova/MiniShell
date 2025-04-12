/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:53:00 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 12:02:23 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_all_chars(char	*str, char	c, char i)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] != c && str[i] != i)
			return (0);
		i++;
	}
	return (1);
}
int	check_parse_errors(t_cmd *cmd)
{
	int	i;

	i = 0;
	if(cmd->arg_count < 1)
	{
		printf("parse error near token '|'\n");
		return (1);
	}
	while(cmd->redirs[i])
	{
		if(is_all_chars(cmd->redirs[i], '<', '>'))
		{
			printf("parse error: %s\n", cmd->redirs[i]);
			return (1);
		}
		if(has_invalid_redirection(cmd->redirs[i]))
			return (1);
		i++;
	}
	return (0);
}
