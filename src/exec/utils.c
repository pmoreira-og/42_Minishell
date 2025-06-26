/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:57:09 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/26 11:42:54 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_all(t_cmd *cmd_list, t_hell *shell)
{
	int		status;
	t_cmd	*tmp;

	tmp = cmd_list;
	status = 0;
	(void) shell;
	while (tmp)
	{
		if (tmp->pid > 0)
			get_status(tmp->pid);
		tmp = tmp->next;
	}
}

int	prepare_heredocs(t_cmd *cmd_list)
{
	t_cmd			*cmd;
	t_redirection	*redir;
	int				flag;

	cmd = cmd_list;
	flag = 0;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == LIM)
			{
				flag = 1;
				do_heredoc(redir);
				if (get_hell(NULL)->status == 130)
					return (flag);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (flag);
}
