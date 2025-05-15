/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:06:07 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/15 14:10:02 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	find_non_expand(char *input, char **start, char **end)
{
	t_bool quote;
	t_bool d_quote;

	*start = NULL;
	*end = NULL;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_quotes(*input, &quote, &d_quote);
		if (quote) {
			*start = input;
			input++;
			while (*input && (*input != '\''))
				input++;
			if (*input == '\'')
			{
				*end = input + 1;
				return;
			}
		}
		if (*input == '"' && !quote)
			d_quote = !d_quote;
		input++;
	}
}

void	literal(char **ptr, char *s, char *endptr, t_env **env)
{
	char	*start;
	char	*end;
	char	*temp;
	char	*rest;

	find_non_expand(s, &start, &end);
	rest = NULL;
	if (start && end)
	{
		if(start > s)
			*ptr = expand_vars(s, start, env);
		temp = new_word(start + 1, end - 1);
		*ptr = ft_expand(*ptr, temp, &temp);
		if (*end)
		{
			literal(&rest, end, endptr, env);
			*ptr = ft_expand(*ptr, rest, &rest);
		}
	}
	else
		*ptr = expand_vars(s, endptr, env);
}
