/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:48:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/01 13:44:45 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "pipex.h"
# include "structs.h"

# define HIST_FILE "minishell_history"

// parse:
void	print_input(char *input, t_hell *data);
char	**ft_params(const char *start, const char *end);

// miscs:
void	printascii(void);
int		get_history_fd(t_hell *cmd);
void	load_history(t_hell *cmd);
void	save_history(char *input, t_hell *cmd);

// built in functions:
void	mini_echo(t_cmd *cmd);
void	mini_pwd(t_cmd *cmd);
void	mini_cd(t_cmd *cmd, t_env *env);
void	mini_env(t_env *env);
void	mini_exit(t_hell *hell);

// enviroment management:
void	init_env(t_env **env, char **envp);
void	ft_setenv(t_env **env, char *var, char *value);

// Utils
void	armageddon(t_hell *data);
t_hell	*init_hell(int ac, char **av,char **envp);
t_bool	is_builtin(char *s);
t_bool	is_command(char *s, char **path);
int		check_prev(t_token *prev, t_token *current);

#endif