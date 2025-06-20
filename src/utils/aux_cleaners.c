/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cleaners.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:08:31 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/20 10:59:13 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Clear all cmd data and set cmd as NULL.
/// @param data Main struct
void	clean_cmds(t_hell *data)
{
	t_cmd	*temp;
	t_cmd	*next_cmd;

	temp = data->cmd;
	while (temp)
	{
		next_cmd = temp->next;
		delete_cmd(temp);
		temp = next_cmd;
	}
	data->cmd = NULL;
}

/// @brief Clear all data and set pointer as NULL.
/// @param data Main struct
void	clean_env(t_hell *data)
{
	t_env	*temp;
	t_env	*next_node;

	temp = data->env;
	while (temp)
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
	while (temp)
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
	while (temp)
	{
		next_node = temp->next;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->backup)
			free(temp->backup);
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
