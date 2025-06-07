/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:39:15 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/07 18:12:51 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_token(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == REDIR_OUT || tok->type == PIPE || tok->type == REDIR_IN)
		return (1);
	return (0);
}

char	*valid_format(t_token *tok)
{
	t_token	*temp;

	if (!tok)
		return (0);
	temp = tok;
	if (temp->type == PIPE)
		return (temp->cmd);
	while (temp->next)
		temp = temp->next;
	if (temp->prev)
	{
		temp = temp->prev;
		if (special_token(temp))
			return (TOKEN_NEWLINE);
	}
	return (NULL);
}

int	valid_input(t_token *tok, t_hell *data)
{
	t_bool	cmd;
	t_token	*temp;
	char	*error;

	if (!tok)
		return (0);
	temp = tok;
	cmd = FALSE;
	error = valid_format(tok);
	if (error)
		return (parser_error(error, 2), 0);
	while (temp->next)
	{
		if (temp && temp->cmd)
			temp->expanded = has_expansion(temp->cmd);
		process_str(&temp->cmd, temp->cmd, data);
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

void	token_type(char *s, t_token *tok, t_token *prev, char **path)
{
	if (check_prev(prev, tok))
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

void	tokenize(char *input, t_hell *data)
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
		return (ft_clean_matrix(matrix), merror("tokenize:head"));
	temp = data->tokens;
	while (matrix[++i])
	{
		token_type(matrix[i], temp, temp->prev, data->path);
		temp->next = ft_calloc(1, sizeof(t_token));
		if (!temp->next)
			return (ft_clean_matrix(matrix), merror("tokenize:node"));
		temp->cmd = ft_strdup(matrix[i]);
		if (!temp->cmd)
			return (mini_cleaner(matrix, data), merror("tokenize:node:cmd"));
		temp->next->prev = temp;
		temp = temp->next;
	}
	ft_clean_matrix(matrix);
}
