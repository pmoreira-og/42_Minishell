/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:03:58 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/30 12:53:57 by pmoreira         ###   ########.fr       */
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
}	t_type;

typedef struct s_hell
{
	struct s_cmd	*cmd;
	struct s_env	*env;
	struct s_token	*tokens;
	char			**envp;
	char			**path;
	int				status;
	int				hist_fd;
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
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

#endif