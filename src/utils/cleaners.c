/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:10:40 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/15 16:03:50 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	clean_cmds(t_cmd *cmd)
// {
	
// }

// void	clean_env(t_env *env)
// {
	
// }
void	clean_list(t_token **toks)
{
	t_token	*temp;

	if (*toks == 0)
		return ;
	else
	{
		temp = *toks;
		while ((*toks)->next != 0)
		{
			if ((*toks)->args)
				ft_clean_matrix((*toks)->args);
			if ((*toks)->cmd)
				free ((*toks)->cmd);
			temp = (*toks)->next;
			free((*toks));
			(*toks) = temp;
		}
		if ((*toks)->args)
			ft_clean_matrix((*toks)->args);
		if ((*toks)->cmd)
			free ((*toks)->cmd);
		free((*toks));
	}
	*toks = NULL;
}
// void	clean_list(t_token **toks)
// {
// 	t_token	*temp;

// 	if (!toks)
// 		return ;
// 	temp = toks;
// 	while (toks->next)
// 	{
// 		temp = temp->next;
		
// 		free(toks);
// 		toks = temp;
// 	}
// 	if (toks->args)
// 			ft_clean_matrix(toks->args);
// 		if (toks->cmd)
// 			free (toks->cmd);
// 		free(toks);
// 	// toks = NULL;
// }

void	armageddon(t_hell *data)
{
	// if (data->cmd)
	// 	clean_cmds(data->cmd);
	// if (data->env)
	// 	clean_env(data->env);
	if (data->path)
		ft_clean_matrix(data->path);
	if (data->envp)
		ft_clean_matrix(data->envp);
	if (data->hist_fd >= 0)
		close(data->hist_fd);
}
