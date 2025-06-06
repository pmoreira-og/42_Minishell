/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:21:45 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/06 20:55:28 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_expand_zones(char *input)
{
	int		count;
	t_bool	quote;
	t_bool	d_quote;

	if (!input)
		return (0);
	count = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_char_quote((const char **)&input, &quote, &d_quote);
		if (!quote && !d_quote && *input == '$' && is_quotes(*(input + 1)))
			count++;
		input++;
	}
	return (count);
}

void	check_quote_spaces(const char **s, t_bool *quote, t_bool *d_quote)
{
	if (!s)
		return ;
	check_quotes(**s, quote, d_quote);
	if (**s == '\\' && *(*s + 1) && is_quotes(*(*s + 1)))
	{
		*quote = FALSE;
		*d_quote = FALSE;
	}
}

char	*remove_zones(char **ptr, char *input)
{
	char	*output;
	t_bool	quote;
	t_bool	d_quote;
	int		i;

	if (!ptr || !input)
		return (NULL);
	output = malloc(ft_strlen(input) - count_expand_zones(input) + 1);
	if (!output)
		return (merror("remove_zones"), NULL);
	i = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_char_quote((const char **)&input, &quote, &d_quote);
		if (!(!quote && !d_quote && *input == '$' && is_quotes(*(input + 1))))
			output[i++] = *input;
		input++;
	}
	output[i] = '\0';
	free(*ptr);
	return (output);
}
