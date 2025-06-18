/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:57:09 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/18 13:57:37 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_heredoc(t_cmd *cmd)
{
	t_redirection	*temp;

	temp = cmd->redir_in;
	while (temp && temp->next)
	{
		if (temp->type == LIM)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

t_bool	need_fork(t_cmd *cmd)
{
	if (cmd->is_piped)
		return (TRUE);
	if (has_heredoc(cmd))
		return (TRUE);
	return (FALSE);
}
