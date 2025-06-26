/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cleaners2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:10 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/26 11:45:33 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_redir(t_redirection **redir)
{
	t_redirection	*temp;

	while (*redir)
	{
		temp = (*redir)->next;
		if ((*redir)->filename)
		{
			free((*redir)->filename);
			(*redir)->filename = NULL;
		}
		if ((*redir)->limiter)
		{
			free((*redir)->limiter);
			(*redir)->limiter = NULL;
		}
		if ((*redir)->fd > 2)
			close((*redir)->fd);
		free(*redir);
		*redir = temp;
	}
}

void	delete_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		ft_clean_matrix(cmd->args);
	if (cmd->envp)
		ft_clean_matrix(cmd->envp);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->redirs)
		clear_redir(&cmd->redirs);
	free(cmd);
	cmd = NULL;
}
