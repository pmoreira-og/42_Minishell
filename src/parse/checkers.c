/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:55:22 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/20 10:32:05 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(int c)
{
	return (c == '\'' || c == '\"');
}

void	check_char_quote(const char **s, t_bool *quote, t_bool *d_quote)
{
	if (!s)
		return ;
	check_quotes(**s, quote, d_quote);
	if (**s == 92 && *(*s + 1) && is_quotes(*(*s + 1)))
	{
		*quote = FALSE;
		*d_quote = FALSE;
		*s += 1;
	}
}

int	quotes_check(char *input)
{
	t_bool	quote;
	t_bool	d_quote;

	if (!input)
		return (0);
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_char_quote((const char **) &input, &quote, &d_quote);
		input++;
	}
	if (d_quote || quote)
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

void	check_quotes(int c, t_bool *quote, t_bool *d_quote)
{
	if (c == '\'' && *quote)
	{
		*quote = FALSE;
		return ;
	}
	else if (c == '\"' && *d_quote)
	{
		*d_quote = FALSE;
		return ;
	}
	if (c == '\'' && !(*d_quote))
	{
		*quote = TRUE;
		return ;
	}
	else if (c == '\"' && !(*quote))
	{
		*d_quote = TRUE;
		return ;
	}
}
