/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:16 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/29 17:45:21 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

typedef struct s_env		t_env;
typedef struct s_shelldata	t_shelldata;
typedef struct s_cmd t_cmd;

void	pwd(void);
int	cd_command(char *path);

void	echo_command(char **arg);

t_env	*build_env_list(char **envp);
t_env	*find_env(t_env *env_list, const char *key);
t_env	*create_env_variable(const char *key, const char *value);
void	env_command(t_env *env, char **args);

char	*ft_strndup(const char *s, size_t n);
t_env	*create_env_node(const char *env_entry);
void	print_env_list(t_env *env_list);
void	free_env_list(t_env *env_list);
int		ft_strcmp(const char *s1, const char *s2);

void	exit_command(char **args, t_shelldata *shell);

void	export_command(t_env **env, char **args, struct s_shelldata *shell);

void	print_sorted_env(t_env **arr, int count);
void	bubble_sort_env(t_env **arr, int count);

void	sort_and_print_env(t_env **env);

int		set_env(t_env **env_list, const char *key, const char *value);
int		unset_env(t_env **env_list, const char *key);
void	unset_command(t_env **env, char **args);
void	free_command(t_cmd *cmd);

#endif
