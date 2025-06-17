/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:03:58 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/17 11:06:48 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

/// @brief Enumeration of all possible node types
/// @param CMD Commands
/// @param ARG Versatile arguments
/// @param PIPE |
/// @param REDIR_IN <
/// @param REDIR_HERE_DOC <<
/// @param LIM Arg after here_doc
/// @param REDIR_OUT >
/// @param REDIR_OUT_APPEND >>
/// @param BUILT_IN echo cd pwd export unset env exit
typedef enum s_type
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_HERE_DOC,
	LIM,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	BUILT_IN,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
}	t_type;

typedef struct s_hell
{
	struct s_cmd	*cmd;
	struct s_env	*env;
	struct s_export	*export;
	struct s_token	*tokens;
	char			**envp;
	char			**path;
	int				status;
	t_bool			debug;
	t_bool			no_env;
	int				cmd_count;
	int				lines;
	int				hist_fd;
}	t_hell;

typedef struct s_redirection
{
	t_type					type;
	char					*filename;
	char					*limiter;
	int						fd;
	struct s_redirection	*next;
}	t_redirection;

/// @brief Command Structure
/// @param argc Number of tokens
/// @param args Matrix that contains command plus args
/// @param redir_in List of t_redirection nodes
/// @param redir_out List of t_redirection nodes
/// @param next Next cmd node
typedef struct s_cmd
{
	// Command and arguments
	int					argc;
	char				**args;
	char				*cmd_path;
	t_redirection		*redir_in;
	t_redirection		*redir_out;
	char				*delimiter;
	int					pipe_in;
	int					pipe_out;
	t_bool				is_piped;
	pid_t				pid;
	t_bool				is_builtin;
	char				**envp;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_token
{
	t_type			type;
	char			*cmd;
	t_bool			expanded;
	t_bool			not_expansive;
	char			**args;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_export
{
	char			*var;
	char			*value;
	struct s_export	*next;
}	t_export;

#endif