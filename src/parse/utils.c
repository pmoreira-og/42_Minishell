/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:39:30 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/29 14:53:29 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_remover(t_hell *data)
{
	t_token	*temp;

	if (!data->tokens)
		return ;
	temp = data->tokens;
	while (temp->next)
	{
		if (temp && !temp->not_expansive 
			&& !(!ft_strcmp(temp->cmd, "\"") || !ft_strcmp(temp->cmd, "\'")))
			temp->cmd = remove_quotes(temp->cmd);
		temp = temp->next;
	}
}

int	valid_input_test(t_token *tok, t_hell *data)
{
	t_bool	cmd;
	t_token	*temp;

	if (!tok)
		return (0);
	temp = tok;
	cmd = FALSE;
	if (!valid_format(tok))
		return (0);
	while (temp->next)
	{
		process_str(&temp->cmd, temp->cmd, data, &temp->not_expansive);
		if (temp->type == PIPE)
			cmd = FALSE;
		if (cmd && (temp->type == CMD || temp->type == BUILT_IN))
			temp->type = ARG;
		if (temp->type == CMD || temp->type == BUILT_IN)
			cmd = TRUE;
		temp = temp->next;
	}
	return (1);
}

void	tokenize_test(char *input, t_hell *data)
{
	char	**matrix;
	int		i;
	t_token	*temp;

	matrix = ft_params(input);
	if (!matrix)
		return ;
	i = -1;
	print_matrix(matrix);
	data->tokens = ft_calloc(1, sizeof(t_token));
	if (!data->tokens)
		return ;
	temp = data->tokens;
	while (matrix[++i])
	{
		token_type(matrix[i], temp, temp->prev, data->path);
		temp->next = ft_calloc(1, sizeof(t_token));
		if (!temp->next)
			return (ft_clean_matrix(matrix));
		if (count_expand_zones(matrix[i]))
			matrix[i] = remove_zones(&matrix[i], matrix[i]);
		temp->cmd = ft_strdup(matrix[i]);
		temp->next->prev = temp;
		temp = temp->next;
	}
	ft_clean_matrix(matrix);
}

void	ft_freed(t_token *tok, char **matrix)
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

void	connect_list(t_token *new_args, t_token *current, t_hell *data)
{
	t_token	*temp;
	t_token	*temp2;

	temp = new_args;
	while(temp->next)
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

void	append_list(t_token *current, t_hell *data)
{
	t_token	*new_args;
	t_token	*temp;
	char	**matrix;
	int		i;

	matrix = ft_params(current->cmd);
	if (!matrix)
		return ft_putstr_fd("Malloc error\n", 2);
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
	connect_list(new_args, current, data);
	return (ft_freed(current, matrix));
}

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
