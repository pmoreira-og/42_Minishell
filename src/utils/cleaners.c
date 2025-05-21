/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:10:40 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/21 12:22:47 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	clean_env(t_env *env)
// {
	
// }

void	clean_cmds(t_hell *data)
{
	t_cmd	*temp;
	t_cmd	*next_cmd;

	temp = data->cmd;
	while (temp)
	{
		next_cmd = temp->next;
		if (temp->args)
		{
			ft_clean_matrix(temp->args);
			temp->args = NULL;
		}
		if (temp->envp)
		{
			ft_clean_matrix(temp->envp);
			temp->envp = NULL;
		}
		if (temp->cmd_path)
		{
			free(temp->cmd_path);
			temp->cmd_path = NULL;
		}
		free(temp);
		temp = next_cmd;
	}
}
void	clean_list(t_hell *data)
{
	t_token	*temp;
	t_token	*next_node;

	temp = data->tokens;
	while(temp)
	{
		next_node = temp->next;
		if (temp->backup)
		{
			free(temp->backup);
			temp->backup = NULL;
		}
		if (temp->cmd)
		{
			free(temp->cmd);
			temp->cmd = NULL;
		}
		if (temp->args)
		{
			ft_clean_matrix(temp->args);
			temp->args = NULL;
		}
		free(temp);
		temp = next_node;
	}
}

void	prepare_next_input(t_hell *data)
{
	data->cmd_count = 0;
	if (data->tokens)
	{
		clean_list(data);
		data->tokens = NULL;
	}
	if (data->cmd)
	{
		clean_cmds(data);
		data->cmd = NULL;
	}
}

void	armageddon(t_hell *data)
{
	if (data->tokens)
	{
		clean_list(data);
		data->tokens = NULL;
	}
	if (data->cmd)
	{
		clean_cmds(data);
		data->cmd = NULL;
	}
	// if (data->env)
	// 	clean_env(data->env);
	if (data->path)
		ft_clean_matrix(data->path);
	// if (data->envp)
	// 	ft_clean_matrix(data->envp);
	if (data->hist_fd >= 0)
		close(data->hist_fd);
	free(data);
}
