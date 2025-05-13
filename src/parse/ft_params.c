/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:23:53 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/13 15:26:11 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!matrix)
		return (0);
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (0);
	// if (*start == '\'')
	// 	start++;
	// if (*(end - 1) == '\'')
	// 	end--;
	while (start < end)
	{
		word[i++] = *start;
		start++;
		// if (*start == '\\')
		// 	start++;
	}
	word[i] = '\0';
	*matrix = word;
	return (1);
}

static void	ft_count(const char *s, int *count, char c)
{
	// const char	*temp;
	int			quotes;

	quotes = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if(*s)
			*count += 1;
		while(*s && *s != c)
		{
			if (is_quotes(*s))
			{
				// temp = s++;
				
				// *count += (*(temp - 1) && *(temp - 1) != c && *temp == *s);
				while (s && *s && (*temp != *s))
					s++;
			}
			s++;
		}
	}
}

// void	process_quotes(const char **s, int c)
// {
// 	while (**s)
// 	{
// 		*s += 1;
// 		while (**s && (**s != c))
// 			*s += 1;
// 	}
// }

static int	proc_str(char **matrix, const char *s, char c, int *index)
{
	const char	*start;

	while (*s)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
		{
			if (is_quotes(*s))
				
		}
		
		if (!ft_add_word(&matrix[(*index)++], start, s))
			return (ft_free(matrix, *index), 0);
	}
	return (1);
}

char	**ft_params(const char *start, char c)
{
	char	**matrix;
	int		size;
	int		index;

	if (!start)
		return (NULL);
	size = 0;
	ft_count(start, &size, c);
	printf("Words: %d\n", size);
	// return (NULL);
	if (size == 0)
		return (NULL);
	matrix = (char **)malloc(sizeof(char *) * (size + 1));
	if (!matrix)
		return (NULL);
	matrix[size] = NULL;
	index = 0;
	if (!proc_str(matrix, start, c, &index))
		return (NULL);
	// return (NULL);
	return (matrix);
}
