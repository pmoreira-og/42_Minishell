/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:57:09 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/24 12:31:38 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_all(t_cmd *cmd_list, t_hell *shell)
{
	int		status;
	t_cmd	*tmp;

	tmp = cmd_list;
	status = 0;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFEXITED(status))
				shell->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->status = 128 + WTERMSIG(status);
		}
		tmp = tmp->next;
	}
}

void	prepare_heredocs(t_cmd *cmd_list)
{
	t_cmd			*cmd;
	t_redirection	*redir;

	cmd = cmd_list;
	while (cmd)
	{
		redir = cmd->redir_in;
		while (redir)
		{
			if (redir->type == LIM)
				do_heredoc(redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
