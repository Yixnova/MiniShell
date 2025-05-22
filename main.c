/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:53:08 by busseven          #+#             */
/*   Updated: 2025/04/06 17:36:58 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int		count_input_len(char *str)
{
	int	i;
	int	in_quotes;
	int	count;
	int	type;

	in_quotes = 0;
	type = 0;
	i = 0;
	count = ft_strlen(str);
	while(str[i])
	{
		if(in_quotes == 0 && is_in_str("\"\'", str[i]))
		{
			in_quotes = 1;
			type = str[i];
		}
		if(in_quotes == 1 && str[i] == type)
			in_quotes = 0;
		if(in_quotes == 0 && str[i] == '\n' && str[i - 1] == '|')
			count--;
		i++;
	}
	return (count);
}
char	*edit_input(char	*str)
{
	int		i;
	int		n;
	char	*new;
	t_lineparse	data;

	i = 0;
	data.in_quotes = 0;
	data.type = 0;
	n = 0;
	data.count = count_input_len(str);
	new = ft_calloc(data.count, 1);
	while(str[i] && n < data.count)
	{
		if(data.in_quotes == 0 && is_in_str("\"\'", str[i]))
		{
			data.in_quotes = 1;
			data.type = str[i];
		}
		else if(data.in_quotes == 1 && str[i] == data.type)
			data.in_quotes = 0;
		if(data.in_quotes == 0 && str[i] == '\n' && str[i - 1] == '\n')
		{
			i++;
			continue ;
		}
		else if(data.in_quotes == 0 && str[i] == '\n' && str[i - 1] == '|')
			new[n] = ' ';
		else
			new[n] = str[i];
		i++;
		n++;
	}
	new[n] = '\0';
	free(str);
	return (new);
}

int		count_inputs(char *line)
{
	int	i;
	t_lineparse	data;

	i = 0;
	data.count = 0;
	data.in_quotes = 0;
	data.type = 0;
	data.on_word = 0;
	while(line[i])
	{
		if(data.on_word == 0 && line[i] != '\n')
		{
			data.on_word = 1;
			data.count++;
		}
		if(data.in_quotes == 0 && is_in_str("\"\'", line[i]))
		{
			data.in_quotes = 1;
			data.type = line[i];
		}
		else if(data.in_quotes == 1 && line[i] == data.type)
			data.in_quotes = 0;
		if(data.on_word == 1 && data.in_quotes == 0 && line[i] == '\n' 
			&& line[i - 1] != '|' && line[i - 1] != '\n')
			data.on_word = 0;
		i++;
	}
	return (data.count);
}
char	**make_input_arr(char	*line)
{
	char		**arr;
	int			i;
	int			n;
	t_lineparse	data;

	i = 0;
	n = 0;
	data.type = 0;
	data.in_quotes = 0;
	data.start = 0;
	data.count = count_inputs(line);
	arr = ft_calloc(data.count + 1, sizeof(char *));
	while (data.count - 1 >= 0)
	{
		data.on_word = 0;
		data.start = n;
		while (line[n])
		{
			if(data.on_word == 0 && line[n] != '\n')
				data.on_word = 1;
			if(data.in_quotes == 0 && is_in_str("\"\'", line[n]))
			{
				data.in_quotes = 1;
				data.type = line[n];
			}
			else if(data.in_quotes == 1 && line[n] == data.type)
				data.in_quotes = 0;
			if(data.on_word == 1 && data.in_quotes == 0 && line[n] == '\n' 
				&& line[n - 1] != '|' && line[n - 1] != '\n')
				break ;
			n++;
		}
		arr[i] = ft_substr(line, data.start, n - data.start + 1);
		arr[i] = edit_input(arr[i]);
		i++;
		data.count--;
	}
	return (arr);
}
void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	process_input(t_shelldata *shell)
{
	t_cmd	*temp;

	g_signal_flag = 0;
	if (tokenize_input(shell))
		return ;
	init_parsedata(shell);
	if (edit_cmds_arr(shell, *(shell->cmds), 0, 0))
		return ;
	temp = *(shell->cmds);
	while (temp)
	{
		if (temp->has_hd)
			make_cmd_heredocs(temp, shell);
		if (g_signal_flag == 1)
			return ;
		temp = temp->next;
	}
	if (*(shell->cmds) && (*(shell->cmds))->args
		&& (*(shell->cmds))->next == NULL
		&& !ft_strcmp((*(shell->cmds))->args[0], "exit"))
	{
		exit_command((*(shell->cmds))->args, shell);
		return ;
	}
	start_processes(shell, shell->cmds);
}

void	iterate_input_arr(char **input_arr, t_shelldata *shell)
{
	int	i;

	i = 0;
	while (input_arr && input_arr[i])
	{
		shell->input = input_arr[i];
		if (!shell->input)
		{
			free_shell(shell);
			ft_putendl_fd("exit", 1);
			exit (0);
		}
		if (shell->input[0] != '\0')
			process_input(shell);
		if (!input_arr || !input_arr[i])
			return ;
		i++;
		free_input_data(shell);
	}
}

void	handle_input_and_history(t_shelldata *shell)
{
	while (1)
	{
		shell->read_line = readline("myshell$ ");
		if (!shell->read_line)
		{
			ft_putendl_fd("exit", 1);
			free(shell->read_line);
			free_2d_char(shell->envp);
			free_env_list(shell->env);
			free(shell);
			break ;
		}
		shell->input_arr = make_input_arr(shell->read_line);
		iterate_input_arr(shell->input_arr, shell);
		free_2d_char(shell->input_arr);
		free(shell->read_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shelldata	*shell;

	(void)argc;
	(void)argv;
	errno = 0;
	shell = ft_calloc(1, sizeof(t_shelldata));
	if (!shell)
	{
		ft_putendl_fd("Malloc error", 2);
		return (EXIT_FAILURE);
	}
	shell->env = build_env_list(envp);
	set_envp(shell, shell->env, 0);
	shell->iteration_count = 0;
	if (!shell->env)
	{
		ft_putendl_fd("Error", 2);
		return (EXIT_FAILURE);
	}
	disable_echoctl();
	setup_signals();
	handle_input_and_history(shell);
	return (EXIT_SUCCESS);
}
