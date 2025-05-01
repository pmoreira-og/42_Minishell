/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:39:15 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/01 14:32:09 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	token_type(char *s, t_token *tok , t_token *prev, char **path)
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

int	valid_input(t_token *tok)
{
	t_bool	cmd;
	t_token	*temp;

	temp = tok;
	cmd = FALSE;
	while (temp->next)
	{
		if (temp->type == CMD || temp->type == BUILT_IN)
			cmd = TRUE;
		temp = temp->next;
	}
	if (temp->type == REDIR_HERE_DOC)
		return (0);
	else if (temp->type == REDIR_OUT)
		return (0);
	else if (temp->type == REDIR_OUT_APPEND)
		return (0);
	else if (temp->type == REDIR_IN)
		return (0);
	if (!cmd)
		return (0);
	return (1);
}

void	print_token(t_token *toks)
{
	t_token	*temp;

	temp = toks;
	while (temp->next)
	{
		printf("[%s]: %d\n", temp->cmd, temp->type);
		temp = temp->next;
	}
	if (!valid_input(toks))
		printf("inpu invalido!");
}

// char	*get_end(char *s)
// {
// 	t_bool	inside;

// 	inside = FALSE;
// 	if (!s)
// 		return (NULL);
// 	while(*s)
// 	{
// 		if (*s == '\"')
// 			inside == TRUE;
		
// 	}
// }

void	print_input(char *input, t_hell *data)
{
	char	**matrix;
	int		i;
	t_token	*temp;

	matrix = ft_params(input, &input[ft_strlen(input)]);
	if (!matrix)
		return ;
	i = -1;
	temp = data->tokens;
	while (matrix[++i])
	{
		token_type(matrix[i], temp, temp->prev, data->path);
		temp->next = ft_calloc(1, sizeof(t_token));
		if (!temp->next)
			return ;
		temp->cmd = ft_strdup(matrix[i]);
		temp->next->prev = temp;
		temp = temp->next;
	}
	print_token(data->tokens);
	ft_clean_matrix(matrix);
}

