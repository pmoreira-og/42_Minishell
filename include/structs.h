/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:03:58 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/09 14:00:20 by pmoreira         ###   ########.fr       */
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
	int				hist_fd;
}	t_hell;

typedef struct s_redirection
{
	t_type					type;
	char					*filename;  // *For regular file redirections 
	char					*heredoc_delimiter; // *For heredoc
	char					*heredoc_content;   // !Expanded heredoc content
	int						fd;         // !File descriptor used
	struct s_redirection	*next;
} t_redirection;

/// @brief Command Structure
/// @param argc Number of tokens
/// @param args Matrix that contains command plus args
/// @param infile Filename (char *)
/// @param outfile Filename (char *)
/// @param append Flag: 0 for >, 1 for >>
/// @param heredoc Heredoc flag
/// @param delimiter Heredoc demiliter string
/// @param next Next cmd node
typedef struct s_cmd
{
	// Command and arguments
	int					argc;
	char				**args;
	char				*cmd_path;      // *Full path to executable (after path resolution)
	char				*infile;
	char				*outfile;
	char				*delimiter;
	int					pipe_in;        // !Read end of pipe from previous command
	int					pipe_out;       // !Write end of pipe to next command
	t_bool				is_piped;       // *Flag if this command is part of a pipe
	pid_t				pid;            // !Process ID when executed
	t_bool				is_builtin;     // *Flag if this is a shell builtin command
	char				**envp;         // !Copy of environment variables
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