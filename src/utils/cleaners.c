/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:10:40 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/04 11:52:00 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Clear all cmd data but don't set cmd as NULL because of Normi
/// @param data Main struct
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

/// @brief Clear all data and set pointer as NULL.
/// @param data Main struct
void	clean_env(t_hell *data)
{
	t_env	*temp;
	t_env	*next_node;

	temp = data->env;
	while(temp)
	{
		next_node = temp->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		if (temp->var)
		{
			free(temp->var);
			temp->var = NULL;
		}
		free(temp);
		temp = next_node;
	}
	data->env = NULL;
}

/// @brief Clear all data and set pointer as NULL.
/// @param data Main struct
void	clean_export(t_hell *data)
{
	t_export	*temp;
	t_export	*next_node;

	temp = data->export;
	while(temp)
	{
		next_node = temp->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		if (temp->var)
		{
			free(temp->var);
			temp->var = NULL;
		}
		free(temp);
		temp = next_node;
	}
	data->export = NULL;
}

/// @brief Clear all data and set pointer as NULL.
/// @param data Main struct
void	clean_list(t_hell *data)
{
	t_token	*temp;
	t_token	*next_node;

	temp = data->tokens;
	while(temp)
	{
		next_node = temp->next;
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
	data->tokens = NULL;
}

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
