/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:38:44 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:18:39 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_add_word(char **matrix, const char *start, const char *end);
static char		**ft_free(char **matrix, int index);
static char		**ft_alloc_matrix(char const *s, char c);

static char	**ft_alloc_matrix(char const *s, char c)
{
	char	**alloc;
	int		size;

	size = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			size++;
		while (*s != c && *s)
			s++;
	}
	alloc = (char **)ft_calloc((size + 1), sizeof(char *));
	if (alloc == 0)
		return (0);
	return (alloc);
}

static char	**ft_free(char **matrix, int index)
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

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (word == 0)
		return (0);
	while (start < end)
	{
		word[i++] = *start;
		start++;
	}
	word[i] = '\0';
	*matrix = word;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**matrix;
	const char	*start;
	int			index;

	if (s == 0)
		return (0);
	matrix = ft_alloc_matrix(s, c);
	if (matrix == 0)
		return (0);
	index = 0;
	while (*s != 0)
	{
		if (*s != c)
		{
			start = s;
			while (*s != 0 && *s != c)
				s++;
			if (!ft_add_word(&matrix[index++], start, s))
				return (ft_free(matrix, index));
		}
		else
			s++;
	}
	matrix[index] = 0;
	return (matrix);
}
