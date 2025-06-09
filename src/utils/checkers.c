/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:33:17 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/09 11:54:04 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_command(char *s, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], s);
		if (!temp)
			return (merror("is_command:temp"), FALSE);
		if (access(temp, F_OK) != -1)
			return (free(temp), TRUE);
		free(temp);
		i++;
	}
	return (FALSE);
}

t_bool	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo"))
		return (TRUE);
	else if (!ft_strcmp(s, "pwd"))
		return (TRUE);
	else if (!ft_strcmp(s, "cd"))
		return (TRUE);
	else if (!ft_strcmp(s, "env"))
		return (TRUE);
	else if (!ft_strcmp(s, "exit"))
		return (TRUE);
	else if (!ft_strcmp(s, "export"))
		return (TRUE);
	else if (!ft_strcmp(s, "unset"))
		return (TRUE);
	return (FALSE);
}

int	check_prev(t_token *prev, t_token *current)
{
	if (!prev)
		current->type = ARG;
	else if (prev && prev->type == REDIR_IN)
		current->type = INFILE;
	else if (prev && prev->type == REDIR_HERE_DOC)
	{
		current->type = LIM;
		current->not_expansive = TRUE;
	}
	else if (prev && prev->type == REDIR_OUT)
		current->type = OUTFILE;
	else if (prev && prev->type == REDIR_OUT_APPEND)
		current->type = OUTFILE_APPEND;
	else
		current->type = ARG;
	if (current->type == ARG)
		return (0);
	return (1);
}
