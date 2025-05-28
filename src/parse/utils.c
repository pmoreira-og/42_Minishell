/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:39:30 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/28 12:33:15 by pmoreira         ###   ########.fr       */
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

int	valid_input_test(t_token *tok, t_hell *data, t_bool flag)
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
		(void) flag;// if (flag)
		// 	temp->not_expansive = TRUE;
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

void	recall_parser(char **input, t_hell *data)
{
	char	*new_input;
	t_token	*temp;

	temp = data->tokens;
	new_input = NULL;
	while (temp->next)
	{
		new_input = ft_expand(new_input, temp->cmd, NULL);
		if (temp->next)
			new_input = ft_expand(new_input, " ", NULL);
		temp = temp->next;
	}
	prepare_next_input(data);
	free (*input);
	*input = new_input;
	tokenize_test(*input, data);
	valid_input_test(data->tokens, data, TRUE);
}
