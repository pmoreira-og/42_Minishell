/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:50:41 by pmoreira          #+#    #+#             */
/*   Updated: 2025/03/12 15:04:26 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char c)
{
	int	count;

	if (!str)
		return (-1);
	count = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str == '\'')
		{
			str++;
			count += 1;
			while (*str && *str != '\'')
				str++;
			while (*str && *str != c)
				str++;
		}
		if (*str && *str != c)
			count += 1;
		while (*str != c && *str)
			str++;
	}
	return (count);
}
