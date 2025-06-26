/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:14:53 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/26 11:35:57 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirection	*redir_node(t_token *tok)
{
	t_redirection	*node;

	if (!tok)
		return (NULL);
	node = ft_calloc(1, sizeof(t_redirection));
	if (!node)
		return (merror("redir_node"), NULL);
	if (tok->type == LIM)
	{
		node->limiter = ft_strdup(tok->cmd);
		if (!node->limiter)
			return (free(node), merror("redir_node:limiter"), NULL);
	}
	else
	{
		node->filename = ft_strdup(tok->cmd);
		if (!node->filename)
			return (free(node), merror("redir_node:filename"), NULL);
	}
	node->type = tok->type;
	return (node);
}

static t_bool	is_redir_in(t_token *tok)
{
	if (!tok)
		return (FALSE);
	if (tok->type == INFILE)
		return (TRUE);
	if (tok->type == LIM)
		return (TRUE);
	return (FALSE);
}

static t_bool	is_redir_out(t_token *tok)
{
	if (!tok)
		return (FALSE);
	if (tok->type == OUTFILE)
		return (TRUE);
	if (tok->type == OUTFILE_APPEND)
		return (TRUE);
	return (FALSE);
}

static void	append_node(t_redirection **ptr, t_redirection *node)
{
	t_redirection	*temp;

	if (!ptr || !node)
		return ;
	if (!*ptr)
		*ptr = node;
	else
	{
		temp = *ptr;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

int	init_redirs(t_cmd **cmd, t_token *start)
{
	t_redirection	*temp;

	if (!start || !cmd)
		return (0);
	(*cmd)->redirs = NULL;
	temp = NULL;
	while (start->next && start->type != PIPE)
	{
		if (is_redir_in(start) || is_redir_out(start))
		{
			temp = redir_node(start);
			if (!temp)
				return (merror("init_redirs:temp"), 0);
			if (is_redir_in(start))
				append_node(&(*cmd)->redirs, temp);
			else if (is_redir_out(start))
				append_node(&(*cmd)->redirs, temp);
		}
		start = start->next;
	}
	return (1);
}
