/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cleaners2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:31:10 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/10 18:55:09 by pmoreira         ###   ########.fr       */
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
		if ((*redir)->heredoc_content)
		{
			free((*redir)->heredoc_content);
			(*redir)->heredoc_content = NULL;
		}
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
	if (cmd->redir_in)
		clear_redir(&cmd->redir_in);
	if (cmd->redir_out)
		clear_redir(&cmd->redir_out);
	free(cmd);
	cmd = NULL;
}
