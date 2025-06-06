/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   literal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:06:07 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/06 18:54:27 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_str(char *s, char *endptr)
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
// char	*alloc_str(char *s)
// {
// 	char	*output;
// 	int		count;
// 	int		i;
// 	t_bool	quote;
// 	t_bool	d_quote;

// 	if (!s)
// 		return (NULL);
// 	count = 0;
// 	i = 0;
// 	init_proc(NULL, NULL, &quote, &d_quote);
// 	while (s[i])
// 	{
// 		check_quotes(s[i], &quote, &d_quote);
// 		if ((!quote) && s[i] == '\"')
// 			count++;
// 		else if ((!d_quote) && s[i] == '\'')
// 			count++;
// 		if (s[i])
// 			i++;
// 	}
// 	output = ft_calloc(ft_strlen(s) - count + 1, 1);
// 	if (!output)
// 		return (NULL);
// 	return (output);
// }

// char	*remove_quotes(char *s)
// {
// 	char	*output;
// 	int		i;
// 	int		j;
// 	t_bool	quote;
// 	t_bool	d_quote;

// 	i = -1;
// 	j = 0;
// 	output = alloc_str(s);
// 	if (!output)
// 		return (NULL);
// 	init_proc(NULL, NULL, &quote, &d_quote);
// 	while (s[++i])
// 	{
// 		check_quotes(s[i], &quote, &d_quote);
// 		if ((!quote) && s[i] == '\"')
// 			continue ;
// 		if ((!d_quote) && s[i] == '\'')
// 			continue ;
// 		if (s[i])
// 			output[j++] = s[i];
// 	}
// 	free(s);
// 	return (output);
// }

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
	// char	*start;
	// char	*end;
	// char	*temp;
	char	*output;

	if (!s || !endptr || !hell)
		return (NULL);
	// temp = remove_quotes(s, endptr);
	// if (!temp)
	// 	return (merror("handle_expansion:temp"), NULL);
	// start = temp;
	// output = NULL;
	// end = &temp[ft_strlen(temp)];
	// if (end > start) free(temp), 
	output = expand_vars(s, endptr, hell);
	// else
	// 	output = ft_strdup("");
	if (!output)
			return (merror("handle_expansion:output"), NULL);
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
// void	literal(char **ptr, char *s, char *endptr, t_hell *hell)
// {
// 	char	*start;
// 	char	*end;
// 	char	*temp;

// 	while (s < endptr)
// 	{
// 		find_non_expand(s, &start, &end);
// 		if (!start || !end)
// 		{
// 			temp = expand_vars(s, endptr, hell);
// 			*ptr = ft_expand(*ptr, temp, &temp);
// 			break ;
// 		}
// 		if (start > s)
// 		{
// 			temp = expand_vars(s, start, hell);
// 			*ptr = ft_expand(*ptr, temp, &temp);
// 		}
// 		temp = new_word(start, end);
// 		*ptr = ft_expand(*ptr, temp, &temp);
// 		s = end;
// 		if (*s == '\0')
// 			break ;
// 	}
// }
