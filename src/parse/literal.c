/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:06:07 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/15 16:33:48 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *s)
{
	char	*output;
	int		count;
	int		i;
	t_bool	quote;
	t_bool	d_quote;

	count = 0;
	i = -1;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (s[++i])
	{
		check_quotes(s[i], &quote, &d_quote);
		
	}
	free(s);
	return (output);
}

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
				return;
			}
		}
		if (*(input))
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
		temp = new_word(start, end);
		*ptr = ft_expand(*ptr, temp, &temp);
		if (*end)
		{
			literal(&rest, end, endptr, env);
			*ptr = ft_expand(*ptr, rest, &rest);
		}
	}
	else
		*ptr = expand_vars(s, endptr + 1, env);
}
