/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:48:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/20 11:16:07 by pmoreira         ###   ########.fr       */
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
# define ERR_QUOTES "minishell: syntax error: input contains unclosed quotes\n"
# define RED "\001\033[31m\002"
# define RESET "\001\033[0m\002"

// parse:
void	parser(char *input, t_hell *data);
char	**ft_params(const char *start);
void	tokenize(char *input, t_hell *data);
int		valid_input(t_token *tok);
int		quotes_check(char *input);
void	literal(char **ptr, char *s, char *endptr, t_env **env);
void	init_proc(const char **start, const char *s, t_bool *quote, \
	t_bool *d_quote);
void	check_quotes(int c, t_bool *quote, t_bool *d_quote);
int		is_quotes(int c);
char	*new_word(const char *start, const char *end);
char	*expand_vars(char *s, char *end, t_env **env);
char	*ft_expand(char *s1, char *s2, char **temp);
void	process_str(char **ptr, char *s, t_env **env);
char	*remove_quotes(char *s);
void	check_char_quote(const char **s, t_bool *quote, t_bool *d_quote);
int		tab_counter(const char *start, const char *end);
void	skip_expand_name(char **s, char *end);

// miscs:
void	printascii(void);
int		get_history_fd(t_hell *cmd);
void	load_history(t_hell *cmd);
void	save_history(char *input, t_hell *cmd);

// built in functions:
void	mini_echo(t_cmd *cmd, t_env **env);
void	mini_pwd(t_cmd *cmd);
void	mini_cd(t_cmd *cmd, t_env **env);
void	mini_env(t_env *env);
void	mini_exit(t_hell *hell);
void	mini_export(t_env **env, t_cmd *cmd);
void	mini_unset(t_env **env, t_cmd *cmd);

// enviroment management:
void	init_env(t_env **env, char **envp);
void	ft_setenv(t_env **env, char *var, char *value);

// Utils
void	armageddon(t_hell *data);
t_hell	*init_hell(int ac, char **av, char **envp);
t_bool	is_builtin(char *s);
t_bool	is_command(char *s, char **path);
int		check_prev(t_token *prev, t_token *current);
void	clean_list(t_token **toks);

#endif