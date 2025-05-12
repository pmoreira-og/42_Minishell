/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:55:22 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/07 13:58:50 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(int c)
{
	return (c == '\'' || c == '\"');
}

int	quotes_check(char *input)
{
	int	quotes;
	int	d_quotes;

	quotes = 0;
	d_quotes = 0;
	if (!input)
		return (0);
	while (*input)
	{
		if (*input == '\'')
			quotes++;
		if ((quotes % 2 == 0) && *input == '\"')
			d_quotes++;
		input++;
	}
	if ((d_quotes + quotes) % 2 != 0)
		return (0);
	return (1);
}

int	valid_input(t_token *tok)
{
	t_bool	cmd;
	t_token	*temp;

	temp = tok;
	cmd = FALSE;
	while (temp->next)
	{
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
