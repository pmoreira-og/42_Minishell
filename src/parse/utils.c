/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:39:30 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/27 16:04:33 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	recall_valid_input(t_token *tok)
{
	t_bool	cmd;
	t_token	*temp;

	if (!tok)
		return (0);
	temp = tok;
	cmd = FALSE;
	while (temp->next)
	{
		temp->type = ARG;
		temp->not_expansive = TRUE;
		temp = temp->next;
	}
	return (1);
}

int	recall_check_prev(t_token *prev, t_token *current)
{
	current->not_expansive = TRUE;
	if (!prev)
		current->type = ARG;
	else if (prev && prev->type == REDIR_IN)
		current->type = INFILE;
	else if (prev && prev->type == REDIR_HERE_DOC)
		current->type = LIM;
	else if (prev && prev->type == REDIR_OUT)
		current->type = OUTFILE;
	else if (prev && prev->type == REDIR_OUT_APPEND)
		current->type = OUTFILE;
	else
		current->type = ARG;
	if (current->type == ARG)
		return (0);
	return (1);
}

void	recall_token_type(char *s, t_token *tok, t_token *prev, char **path)
{
	if (recall_check_prev(prev, tok))
		return ;
	else if (is_builtin(s))
		tok->type = BUILT_IN;
	else if (!ft_strcmp(s, ">>"))
		tok->type = REDIR_OUT_APPEND;
	else if (!ft_strcmp(s, ">"))
		tok->type = REDIR_OUT;
	else if (!ft_strcmp(s, "<"))
		tok->type = REDIR_IN;
	else if (!ft_strcmp(s, "<<"))
		tok->type = REDIR_HERE_DOC;
	else if (!ft_strcmp(s, "|"))
		tok->type = PIPE;
	else if (*s && is_command(s, path))
		tok->type = CMD;
}

void	recall_tokenize(char *input, t_hell *data)
{
	char	**matrix;
	int		i;
	t_token	*temp;

	matrix = ft_params(input);
	if (!matrix)
		return ;
	print_matrix(matrix);
	i = -1;
	data->tokens = ft_calloc(1, sizeof(t_token));
	if (!data->tokens)
		return ;
	temp = data->tokens;
	while (matrix[++i])
	{
		recall_token_type(matrix[i], temp, temp->prev, data->path);
		temp->next = ft_calloc(1, sizeof(t_token));
		if (!temp->next)
			return (ft_clean_matrix(matrix));
		if (count_expand_zones(matrix[i]))
			matrix[i] = remove_zones(&matrix[i], matrix[i]);
		process_str(&temp->cmd, matrix[i], data, &temp->not_expansive);
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
	tokenize(*input, data);
	recall_valid_input(data->tokens);
}
