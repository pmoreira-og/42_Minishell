/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:39:15 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/29 16:06:38 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	token_type(char *s, t_token *tok , t_token *prev, char **path)
{
	printf("%s -> \n", s);
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
	else if (is_command(s, path))
		tok->type = CMD;
	// printf("%d\n", tok->type);
}

void	print_token(t_token *toks)
{
	t_token	*temp;
	int		i;

	temp = toks;
	i = 0;
	while (temp->next)
	{
		printf("[%d]: %d\n", i, temp->type);
		i++;
		temp = temp->next;
	}
}

void	print_input(char *input, t_hell *data)
{
	char	**matrix;
	int		i;
	t_token	*temp;

	matrix = ft_parse(input, ' ');
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
		temp->next->prev = temp;
		temp = temp->next;
	}
	print_token(data->tokens);
	ft_clean_matrix(matrix);
}

