/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:58:27 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/05 12:41:55 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_freed(t_token *tok, char **matrix)
{
	if (!tok)
		return ;
	if (matrix)
		ft_clean_matrix(matrix);
	if (tok->cmd)
	{
		free(tok->cmd);
		tok->cmd = NULL;
	}
	if (tok->args)
	{
		ft_clean_matrix(tok->args);
		tok->args = NULL;
	}
	free(tok);
	tok = NULL;
}

static void	connect_list(t_token *new_args, t_token *current, t_hell *data)
{
	t_token	*temp;
	t_token	*temp2;

	temp = new_args;
	while (temp->next)
		temp = temp->next;
	temp2 = temp;
	temp = temp->prev;
	if (current && current->prev)
	{
		new_args->prev = current->prev;
		current->prev->next = new_args;
	}
	else
		data->tokens = new_args;
	if (current && current->next)
	{
		temp->next = current->next;
		current->next->prev = temp;
	}
	ft_freed(temp2, NULL);
}

static void	recall_token(t_token *tok, t_hell *data)
{
	t_bool	cmd;
	t_token	*temp;

	if (!tok)
		return ;
	temp = tok;
	cmd = FALSE;
	while (temp->next)
	{
		if (!cmd && is_builtin(temp->cmd))
		{
			temp->type = BUILT_IN;
			cmd = TRUE;
		}
		else if (!cmd && is_command(temp->cmd, data->envp))
		{
			temp->type = CMD;
			cmd = TRUE;
		}
		else
			temp->type = ARG;
		temp->not_expansive = TRUE;
		temp = temp->next;
	}
}

static void	append_list(t_token *current, t_hell *data)
{
	t_token	*new_args;
	t_token	*temp;
	char	**matrix;
	int		i;

	matrix = ft_params(current->cmd);
	if (!matrix)
		return (ft_putstr_fd("Malloc append error\n", 2));
	i = -1;
	new_args = ft_calloc(1, sizeof(t_token));
	if (!new_args)
		return ;
	temp = new_args;
	while (matrix[++i])
	{
		temp->next = ft_calloc(1, sizeof(t_token));
		if (!temp->next)
			return (ft_clean_matrix(matrix));
		temp->cmd = ft_strdup(matrix[i]);
		temp->next->prev = temp;
		temp = temp->next;
	}
	recall_token(new_args, data);
	connect_list(new_args, current, data);
	return (ft_freed(current, matrix));
}

/// @brief Create a sub list of args and append it to main list.
void	recall_parser(t_hell *data)
{
	t_token	*temp;
	t_token	*next_node;
	int		i;

	temp = data->tokens;
	while (temp->next)
	{
		i = 0;
		next_node = temp->next;
		ft_count(temp->cmd, &i);
		if (i > 1)
			append_list(temp, data);
		temp = next_node;
	}
}
