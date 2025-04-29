/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:10:40 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/29 11:22:15 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	clean_cmds(t_cmd *cmd)
// {
	
// }

// void	clean_env(t_env *env)
// {
	
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
