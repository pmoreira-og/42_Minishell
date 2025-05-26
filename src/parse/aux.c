/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:21:45 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/26 15:25:33 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

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

int	count_spaces(char *s)
{
	int		count;
	char	*temp;
	int		flag;
	t_bool	quote;
	t_bool	d_quote;

	if (!s)
		return (0);
	count = 0;
	init_proc((const char **) &temp, s, &quote, &d_quote);
	while (*s)
	{
		if (*s && !is_meta(*s))
			temp = s;
		flag = (*s && is_meta(*s));
		check_char_quote((const char **)&s, &quote, &d_quote);
		while (*s && !quote && !d_quote && is_meta(*s))
			s++;
		if (flag && *s)
			count += ((*temp != ' ') + (*s != ' '));
		if (*s)
			s++;
	}
	return (count);
}

char	*add_spaces(char **ptr, char *s)
{
	char	*output;
	char	*start;
	int		i;
	t_bool	quotes[2];

	output = ft_calloc((ft_strlen(s) + count_spaces(s) + 1), 1);
	if (!output)
		return (NULL);
	i = 0;
	init_proc((const char **) &start, s, &quotes[0], &quotes[1]);
	while (*s)
	{
		check_char_quote((const char **)&s, &quotes[0], &quotes[1]);
		if (is_meta(*s) && !quotes[0] && !quotes[1])
		{
			if (s > start && !is_meta(*(s - 1)) && *(s - 1) != ' ')
				output[i++] = ' ';
			output[i++] = *s++;
			if (*s && !is_meta(*s) && *s != ' ')
				output[i++] = ' ';
		}
		else
			output[i++] = *s++;
	}
	return (free(*ptr), output);
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
		return (NULL);
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
