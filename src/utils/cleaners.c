/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:10:40 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/05 12:08:58 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_next_input(t_hell *data)
{
	data->cmd_count = 0;
	if (data->tokens)
		clean_list(data);
	if (data->cmd)
	{
		clean_cmds(data);
		data->cmd = NULL;
	}
}

void	armageddon(t_hell *data)
{
	if (data->tokens)
		clean_list(data);
	if (data->env)
		clean_env(data);
	if (data->export)
		clean_export(data);
	if (data->cmd)
	{
		clean_cmds(data);
		data->cmd = NULL;
	}
	if (data->path)
		ft_clean_matrix(data->path);
	if (data->hist_fd >= 0)
		close(data->hist_fd);
	rl_clear_history();
	free(data);
}
