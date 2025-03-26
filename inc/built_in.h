/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:08:16 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 13:57:17 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

void	pwd(void);
void	cd_command(char *path);

void	echo_command(char **arg);

t_env	*build_env_list(char **envp);
t_env	*find_env(t_env *env_list, const char *key);
t_env	*create_env_variable(const char *key, const char *value);
void	env_command(t_env *env, char **args);
void	export_command(t_env **env, char **args);
void	unset_command(t_env **env, char **args);
int		set_env(t_env **env_list, const char *key, const char *value);
int		unset_env(t_env **env_list, const char *key);

void	exit_command(char **args, t_shelldata *shell);

t_env	*create_env_node(const char *env_entry);
void	free_env_list(t_env *env_list);
void	print_env_list(t_env *env_list);

#endif
