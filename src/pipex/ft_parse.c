/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:23:53 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/21 16:40:06 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_free(char **matrix, int index)
{
	while (index > 0)
		free(matrix[--index]);
	free(matrix);
	return (0);
}

static int	ft_add_word(char **matrix, /*const*/ char *start, /*const*/ char *end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (word == 0)
		return (0);
	if (*start == '\'')
		start++;
	if (*(end - 1) == '\'')
		end--;
	while (start < end)
	{
		word[i++] = *start;
		start++;
		if (*start == '\\')
			start++;
	}
	word[i] = '\0';
	*matrix = word;
	return (1);
}

static void	ft_count_words(/*const*/ char *str, int *count, char c)
{
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str == '\'')
		{
			str++;
			*count += 1;
			while (*str && *str != '\'')
				str++;
			while (*str && *str != c)
				str++;
		}
		if (*str && *str != c)
			*count += 1;
		while (*str != c && *str)
			str++;
	}
}

static int	process_str(char **matrix, /*const*/ char *s, char c, int *index)
{
	/*const*/ char	*start;

	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = s;
		if (*s == '\'')
		{
			s++;
			while (*s && *s != '\'')
				s++;
			while (*s && *s != c)
				s++;
		}
		else
		{
			while (*s && *s != c)
				s++;
		}
		if (!ft_add_word(&matrix[(*index)++], start, s))
			return (ft_free(matrix, *index), 0);
	}
	return (1);
}

char	**ft_parse(/*const*/ char *s, char c)
{
	char	**matrix;
	int		size;
	int		index;

	if (!s)
		return (NULL);
	size = 0;
	ft_count_words(s, &size, ' ');
	if (size == 0)
		return (NULL);
	matrix = (char **)malloc(sizeof(char *) * (size + 1));
	if (!matrix)
		return (NULL);
	matrix[size] = NULL;
	index = 0;
	if (!process_str(matrix, s, c, &index))
		return (NULL);
	return (matrix);
}
