/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:48:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/25 12:33:51 by pmoreira         ###   ########.fr       */
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
# include "parse.h"

# define HIST_FILE "minishell_history"

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_hell
{
	struct s_cmd	*cmd;
	struct s_env	*env;
	int				status;
}	t_hell;

/// @brief Command Structure
/// @param argc Number of tokens
/// @param argv Matrix that contains command plus args
/// @param infile Filename (char *)
/// @param outfile Filename (char *)
/// @param append Flag: 0 for >, 1 for >>
/// @param heredoc Heredoc flag
/// @param delimiter Heredoc demiliter string
/// @param next Next cmd node
typedef struct s_cmd
{
	int				argc;
	int				hist_fd;
	char			**argv;
	char			*infile;
	char			*outfile;
	t_bool			append;
	t_bool			heredoc;
	char			*delimiter;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	t_type			type;
	char			*cmd;
	char			**args;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

// miscs:
void	printascii(void);
int		get_history_fd(t_cmd *cmd);
void	load_history(t_cmd *cmd);
void	save_history(char *input, t_cmd *cmd);

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

#endif