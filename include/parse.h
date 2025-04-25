/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:03:58 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/24 15:05:41 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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
}	t_type;

void	print_input(char *input);

#endif