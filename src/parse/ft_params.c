/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:23:53 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/02 11:49:35 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free(char **matrix, int index)
{
	while (index > 0)
		free(matrix[--index]);
	free(matrix);
	return (0);
}

static int	ft_add_word(char **matrix, const char *start, const char *end)
{
	char	*word;
	int		i;
	t_bool	quote;
	t_bool	d_quote;

	i = 0;
	if (!matrix)
		return (0);
	word = malloc(end - start - tab_counter(start, end) + 1);
	if (!word)
		return (0);
	init_proc(NULL, NULL, &quote, &d_quote);
	while (start < end)
	{
		check_char_quote(&start, &quote, &d_quote);
		if (*start && *start == '\\' && !quote)
			start++;
		if (*start)
			word[i++] = *start++;
	}
	word[i] = '\0';
	*matrix = word;
	return (1);
}

void	ft_count(const char *input, int *count)
{
	t_bool		quote;
	t_bool		d_quote;
	const char	*start;

	init_proc(&start, input, &quote, &d_quote);
	while (*input)
	{
		check_char_quote(&input, &quote, &d_quote);
		if (ft_isspace(*input) && !quote && !d_quote)
		{
			if (input > start)
				(*count)++;
			start = input + 1;
		}
		input++;
	}
	if (input > start)
		(*count)++;
}

static int	proc_str(char **matrix, const char *s, int *index)
{
	t_bool		quote;
	t_bool		d_quote;
	const char	*start;

	init_proc(&start, s, &quote, &d_quote);
	while (*s)
	{
		check_char_quote(&s, &quote, &d_quote);
		if (ft_isspace(*s) && !quote && !d_quote)
		{
			if (s > start)
			{
				if (!ft_add_word(&matrix[(*index)++], start, s))
					return (ft_free(matrix, *index), 0);
			}
			start = s + 1;
		}
		s++;
	}
	if (s > start)
	{
		if (!ft_add_word(&matrix[(*index)++], start, s))
			return (ft_free(matrix, *index), 0);
	}
	return (1);
}

char	**ft_params(const char *start)
{
	char	**matrix;
	int		size;
	int		index;

	if (!start)
		return (NULL);
	size = 0;
	ft_count(start, &size);
	if (size == 0)
		return (NULL);
	matrix = (char **)malloc(sizeof(char *) * (size + 1));
	if (!matrix)
		return (merror("ft_params:matrix"), NULL);
	matrix[size] = NULL;
	index = 0;
	if (!proc_str(matrix, start, &index))
		return (merror("ft_params:words"), NULL);
	return (matrix);
}
