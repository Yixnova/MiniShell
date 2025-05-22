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
	int		in_quotes;
	int		type;
	char	*new;

	i = 0;
	in_quotes = 0;
	type = 0;
	n = 0;
	new = ft_calloc(count_input_len(str), 1);
	while(str[i])
	{
		if(in_quotes == 0 && is_in_str("\"\'", str[i]))
		{
			in_quotes = 1;
			type = str[i];
		}
		else if(in_quotes == 1 && str[i] == type)
		{
			in_quotes = 0;
		}
		if(in_quotes == 0 && str[i] == '\n' && str[i - 1] == '\n')
		{
			i++;
			continue ;
		}
		else if(in_quotes == 0 && str[i] == '\n' && str[i - 1] == '|')
			new[n] = ' ';
		else
			new[n] = str[i];
		i++;
		n++;
	}
	free(str);
	return (new);
}

int		count_inputs(t_shelldata *shell, char *line)
{
	int	count;
	int	i;
	int	type;
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	type = 0;
	shell->on_word = 0;
	while(line[i])
	{
		if(shell->on_word == 0 && line[i] != '\n')
		{
			shell->on_word = 1;
			count++;
		}
		if(in_quotes == 0 && is_in_str("\"\'", line[i]))
		{
			in_quotes = 1;
			type = line[i];
		}
		else if(in_quotes == 1 && line[i] == type)
		{
			in_quotes = 0;
		}
		if(shell->on_word == 1 && in_quotes == 0 && line[i] == '\n' && line[i - 1] != '|' && line[i - 1] != '\n')
			shell->on_word = 0;
		i++;
	}
	shell->on_word = 0;
	return (count);
}
char	**make_input_arr(t_shelldata *shell, char	*line)
{
	char	**arr;
	int		i;
	int		n;
	int		count;
	int		type;
	int		in_quotes;
	int		start;

	i = 0;
	n = 0;
	type = 0;
	in_quotes = 0;
	start = 0;
	count = count_inputs(shell, line);
	arr = ft_calloc(count + 1, sizeof(char *));
	while(count - 1 >= 0)
	{
		shell->on_word = 0;
		start = n;
		while(line[n])
		{
			if(shell->on_word == 0 && line[n] != '\n')
			{
				shell->on_word = 1;
			}
			if(in_quotes == 0 && is_in_str("\"\'", line[n]))
			{
				in_quotes = 1;
				type = line[n];
			}
			else if(in_quotes == 1 && line[n] == type)
			{
				in_quotes = 0;
			}
			if(shell->on_word == 1 && in_quotes == 0 && line[n] == '\n' && line[n - 1] != '|' && line[n - 1] != '\n')
				break ;
			n++;
		}
		arr[i] = ft_substr(line, start, n - start + 1);
		arr[i] = edit_input(arr[i]);
		i++;
		count--;
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
		shell->input_arr = make_input_arr(shell, shell->read_line);
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
