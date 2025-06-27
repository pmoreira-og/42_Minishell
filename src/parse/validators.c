/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:00:56 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/27 15:55:13 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limiter(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == LIM)
	{
		if (!ft_strcmp(tok->cmd, ">>"))
			return (0);
		else if (!ft_strcmp(tok->cmd, ">"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "<"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "<<"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "|"))
			return (0);
	}
	return (1);
}

int	check_infile(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == INFILE)
	{
		if (!ft_strcmp(tok->cmd, ">>"))
			return (0);
		else if (!ft_strcmp(tok->cmd, ">"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "<"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "<<"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "|"))
			return (0);
	}
	return (1);
}

int	check_outfile(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == OUTFILE || tok->type == OUTFILE_APPEND)
	{
		if (!ft_strcmp(tok->cmd, ">>"))
			return (0);
		else if (!ft_strcmp(tok->cmd, ">"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "<"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "<<"))
			return (0);
		else if (!ft_strcmp(tok->cmd, "|"))
			return (0);
	}
	return (1);
}

int	check_redirs(t_token *tok)
{
	if (!tok)
		return (0);
	if (!check_limiter(tok))
		return (0);
	if (!check_infile(tok))
		return (0);
	if (!check_outfile(tok))
		return (0);
	return (1);
}

int	check_point(t_hell *data)
{
	if (data->input && !ft_strcmp(data->input, "."))
	{
		ft_printf_fd(2, "minishell: .: filename argument required\n");
		data->status = 2;
		return (1);
	}
	return (0);
}
