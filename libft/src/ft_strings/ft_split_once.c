/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:21:01 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/27 15:02:09 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_once(char *str, char d)
{
	char	**matrix;
	char	*first_half;

	matrix = malloc (sizeof(char *) * 3);
	if (!matrix)
		return (NULL);
	first_half = ft_strchr (str, d);
	if (!first_half)
	{
		matrix[0] = ft_strdup (str);
		matrix[1] = NULL;
		matrix[2] = NULL;
		return (matrix);
	}
	matrix[0] = ft_substr (str, 0, first_half - str);
	matrix[1] = ft_strdup (first_half + 1);
	matrix[2] = NULL;
	return (matrix);
}
