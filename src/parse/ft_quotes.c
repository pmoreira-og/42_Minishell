/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:09:56 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/09 12:50:54 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*alloc_str(char *s, char *endptr)
{
	char	*output;
	int		count;
	t_bool	quote;
	t_bool	d_quote;
	size_t	size;

	if (!s || !endptr)
		return (NULL);
	count = 0;
	size = endptr - s;
	if (size <= 0)
		return (NULL);
	init_proc(NULL, NULL, &quote, &d_quote);
	while (s < endptr)
	{
		check_quotes(*s, &quote, &d_quote);
		if (*s == '\"')
			count++;
		if (*s)
			s++;
	}
	output = ft_calloc(size - count + 1, 1);
	if (!output)
		return (NULL);
	return (output);
}

static char	*alloc_str_quotes(char *s)
{
	char	*output;
	int		count;
	int		i;
	t_bool	quote;
	t_bool	d_quote;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (s[i])
	{
		check_quotes(s[i], &quote, &d_quote);
		if ((!quote) && s[i] == '\"')
			count++;
		else if ((!d_quote) && s[i] == '\'')
			count++;
		if (s[i])
			i++;
	}
	output = ft_calloc(ft_strlen(s) - count + 1, 1);
	if (!output)
		return (NULL);
	return (output);
}

char	*remove_quotes(char *s, char *endptr)
{
	char	*output;
	int		j;
	t_bool	quotes[2];
	ssize_t	size;
	ssize_t	i;

	j = 0;
	output = alloc_str(s, endptr);
	if (!output)
		return (merror("remove_quotes"), NULL);
	size = endptr - s;
	i = -1;
	init_proc(NULL, NULL, &quotes[0], &quotes[1]);
	while (++i < size)
	{
		check_quotes(s[i], &quotes[0], &quotes[1]);
		if (s[i] == '\"')
			continue ;
		if (s[i])
			output[j++] = s[i];
	}
	return (output);
}

char	*remove_both_quotes(char *s)
{
	char	*output;
	int		i;
	int		j;
	t_bool	quote;
	t_bool	d_quote;

	i = -1;
	j = 0;
	output = alloc_str_quotes(s);
	if (!output)
		return (NULL);
	init_proc(NULL, NULL, &quote, &d_quote);
	while (s[++i])
	{
		check_quotes(s[i], &quote, &d_quote);
		if ((!quote) && s[i] == '\"')
			continue ;
		if ((!d_quote) && s[i] == '\'')
			continue ;
		if (s[i])
			output[j++] = s[i];
	}
	return (output);
}
