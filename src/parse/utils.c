/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:39:30 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/05 12:39:10 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_check(char *input)
{
	t_bool		quote;
	t_bool		d_quote;
	char		*error;
	const char	*temp;

	if (!input)
		return (0);
	init_proc(&temp, (const char *) input, &quote, &d_quote);
	while (*temp)
	{
		check_char_quote(&temp, &quote, &d_quote);
		temp++;
	}
	if (d_quote)
		return (parser_error("\"", 2), 0);
	else if (quote)
		return (parser_error("\'", 2), 0);
	error = syntax_error_check(input);
	if (error)
		return (parser_error(error, 2), free(error), 0);
	return (1);
}

void	quotes_remover(t_hell *data)
{
	t_token	*temp;

	if (!data->tokens)
		return ;
	temp = data->tokens;
	while (temp->next)
	{
		if (temp /* && temp->not_expansive == FALSE */
			&& !(!ft_strcmp(temp->cmd, "\"") || !ft_strcmp(temp->cmd, "\'")))
			temp->cmd = remove_quotes(temp->cmd);
		temp = temp->next;
	}
}

void	add_spaces(char **input)
{
	int		count;
	char	*new_input;

	if (!input || !*input)
		return ;
	new_input = NULL;
	count = space_length(*input);
	if (count)
	{
		new_input = space_put(*input, count);
		free (*input);
		*input = new_input;
	}
}
