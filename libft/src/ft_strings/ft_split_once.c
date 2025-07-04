/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:21:01 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/04 10:45:47 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_once(char *str, char d)
{
	char	**matrix;
	char	*first_half;

	matrix = ft_calloc(3, sizeof(char *));
	if (!matrix)
		return (NULL);
	first_half = ft_strchr(str, d);
	if (!first_half)
	{
		matrix[0] = ft_strdup (str);
		if (!matrix[0])
			return (ft_free(matrix, 3));
		return (matrix);
	}
	matrix[0] = ft_substr (str, 0, first_half - str);
	if (!matrix[0])
		return (ft_free(matrix, 3));
	matrix[1] = ft_strdup (first_half + 1);
	if (!matrix[1])
		return (ft_free(matrix, 3));
	return (matrix);
}
