/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:48:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/24 10:49:28 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "structs.h"
# define HIST_FILE "minishell_history"
# define ERR_QUOTES "minishell: syntax error: input contains unclosed quotes\n"
# define ERR_BAD_FORMAT "minishell: syntax error near unexpected token "
# define TOKEN_NEWLINE	"`newline'"
# define HEREDOC_EOF "minishell: warning: here-document at line "
# define HEREDOC_LIM " delimited by end-of-file (wanted "
# define RED "\001\033[31m\002"
# define RESET "\001\033[0m\002"
# define ORANGE "\033[1;38;5;214m"

// # define ft_calloc(x, y) NULL
// # define malloc(x) NULL

// execution:
void	execute_pipeline(t_hell *shell);
void	handle_redirections(t_cmd *cmd);
void	execute_child(t_cmd *cmd, int prev_pipe, int *pipes, t_hell *shell);
int		execute_builtin(t_cmd *cmd, t_hell *shell);
void	do_heredoc(t_redirection *redir);
// void	do_heredoc(t_cmd *cmd);
t_bool	has_heredoc(t_cmd *cmd);
t_bool	need_fork(t_cmd *cmd);
void	try_run(t_hell *data, char **program);
char	*path_handler(char *arg);

// parse:
void	ft_count(const char *input, int *count);
int		valid_input(t_token *tok, t_hell *data);
void	tokenize(char *input, t_hell *data);
void	quotes_remover(t_hell *data);
char	*valid_format(t_token *tok);
void	parser(char **input, t_hell *data);
char	**ft_params(const char *start);
void	tokenize(char *input, t_hell *data);
int		quotes_check(char *input);
void	literal(char **ptr, char *s, char *endptr, t_hell *hell);
void	init_proc(const char **start, const char *s, t_bool *quote, \
	t_bool *d_quote);
void	check_quotes(int c, t_bool *quote, t_bool *d_quote);
int		is_quotes(int c);
char	*new_word(const char *start, const char *end);
char	*expand_vars(char *s, char *end, t_hell *hell);
char	*ft_expand(char *s1, char *s2, char **temp);
void	process_str(char **ptr, char *s, t_hell *hell, t_bool *flag);
char	*remove_quotes(char *s, char *endptr);
void	check_char_quote(const char **s, t_bool *quote, t_bool *d_quote);
int		tab_counter(const char *start, const char *end);
void	skip_expand_name(char **start, char **s, char *end);
int		command_size(t_token *start, t_token **save_ptr, int *cmd_c, \
	t_bool *flag);
char	**build_args(t_token *start, t_cmd **cmd);
char	*get_env(t_env **env, char *name);
void	init_cmds(t_hell *data);
void	get_status(char **result, t_hell *hell, char **s);
void	concat_expand(char **result, char **new_str, t_hell *hell);
int		valid_expand(int c);
int		localized_expansions(char *start, char *end);
int		count_spaces(char *s);
void	pre_process_input(char **input);
char	*expand_heredoc(char *s, char *end, t_hell *hell);
int		count_expand_zones(char *input);
char	*localized_expander(char *start, char *end, t_hell *hell);
char	*remove_zones(char **ptr, char *input);
int		is_meta(int c);
void	parser_error(char *error_msg, int fd);
int		check_cmds(t_token *tok);
void	recall_parser(t_hell *data);
void	token_type(char *s, t_token *tok, t_token *prev, char **path);
char	*syntax_error_check(char *input);
char	*space_put(char *input, int len);
int		space_length(char *input);
int		init_redirs(t_cmd **cmd, t_token *start);
void	input_heredoc(int fd, char *limiter);
t_bool	has_expansion(char *s);
int		check_redirs(t_token *tok);
char	*remove_both_quotes(char *s);
char	*handle_limiter(char *s, t_bool *flag);
char	*get_full_path(char *cmd, char **envp);
t_bool	check_ambiguous(t_token *tok);
void	error_ambiguous(char *s);
void	make_backup(t_token *tok);
void	update_prev_cmd(t_cmd *cmd);

// miscs:
void	printascii(void);
int		get_history_fd(t_hell *cmd);
void	load_history(t_hell *cmd);
char	*get_type(t_type type);
void	save_history(char *input, t_hell *cmd);
void	merror(char *s);

// built in functions:
int		mini_echo(t_cmd *cmd);
int		mini_pwd(t_cmd *cmd);
void	mini_cd(t_cmd *cmd, t_env **env, t_hell *shell);
void	mini_env(t_hell *shell, t_cmd *cmd);
void	mini_exit(t_hell *hell);
void	mini_export(t_env **env, t_export **export, t_cmd *cmd);
void	mini_unset(t_env **env, t_cmd *cmd, t_export **export, t_hell *hell);

// enviroment management:
void	init_env(t_env **env, char **envp);
void	ft_setenv(t_env **env, char *var, char *value);
void	init_export(t_export **export, char **envp);
void	ft_setexport(t_export **export, char *var, char *value);
void	update_env(t_hell *shell);

// Utils
t_hell	*init_hell(int ac, char **av, char **envp);
t_bool	is_builtin(char *s);
t_bool	is_command(char *s, char **path);
int		check_prev(t_token *prev, t_token *current);
void	clean_list(t_hell *data);
void	print_matrix(char **matrix);
void	print_token(t_token *toks);
void	print_redirs(t_cmd *cmd);
void	print_cmd_info(t_hell *data);
int		lst_size(t_cmd *cmd);
void	armageddon(t_hell *data);
void	prepare_next_input(t_hell *data);
void	mini_cleaner(char **matrix, t_hell *data, int status);
char	**copy_env(char **envp);
t_hell	*get_hell(t_hell *hell);
void	signal_handler(t_hell *hell, int flag);
void	stop_parent_signals(void);
char	**ft_getenv(char **envp, char *target, char split);
t_bool	ft_dup(int dst, int src);

// Aux cleaners
void	clean_cmds(t_hell *data);
void	clean_env(t_hell *data);
void	clean_list(t_hell *data);
char	**ft_free(char **matrix, int index);
void	clean_export(t_hell *data);
void	delete_cmd(t_cmd *cmd);
void	ft_clean_matrix(char **matrix);
void	close_all(void);
#endif