/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:06:07 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/09 12:09:35 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_non_expand(char *input, char **start, char **end)
{
	t_bool	quote;
	t_bool	d_quote;

	*start = NULL;
	*end = NULL;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_quotes(*input, &quote, &d_quote);
		if (*input && quote)
		{
			*start = input;
			input++;
			while (*input && (*input != '\''))
				input++;
			if (*input == '\'')
			{
				*end = input + 1;
				return ;
			}
		}
		if (*(input))
			input++;
	}
}

char	*handle_expansion(char *s, char *endptr, t_hell *hell)
{
	char	*output;

	if (!s || !endptr || !hell)
		return (NULL);
	output = expand_vars(s, endptr, hell);
	if (!output)
		return (merror("handle_expansion"), NULL);
	return (output);
}

void	literal(char **ptr, char *s, char *endptr, t_hell *hell)
{
	char	*start;
	char	*end;
	char	*temp;

	while (s < endptr)
	{
		find_non_expand(s, &start, &end);
		if (!start || !end)
		{
			temp = handle_expansion(s, endptr, hell);
			*ptr = ft_expand(*ptr, temp, &temp);
			break ;
		}
		if (start > s)
		{
			temp = handle_expansion(s, start, hell);
			*ptr = ft_expand(*ptr, temp, &temp);
		}
		temp = new_word(start + 1, end - 1);
		*ptr = ft_expand(*ptr, temp, &temp);
		s = end;
		if (*s == '\0')
			break ;
	}
}
