/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:52:59 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:16:57 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(const char *str, const char *target, int inc)
{
	int	i;
	int	pos;

	i = 0;
	if (inc < 0)
		pos = ft_strlen(str) - 1;
	else
		pos = 0;
	while (target[i] != 0)
	{
		if (target[i] == str[pos])
		{
			pos += inc;
			i = 0;
		}
		else
			i++;
	}
	return (pos);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*output;
	unsigned int	max;
	unsigned int	min;
	int				i;

	if (s1 == 0)
		return (0);
	min = ft_count(s1, set, 1);
	max = ft_count(s1, set, -1) + 1;
	if (max == 0)
		output = (char *) malloc(1);
	else
		output = (char *) malloc(((max - min) * sizeof(char)) + 1);
	if (output == 0)
		return (0);
	i = 0;
	while (min < max)
		output[i++] = s1[min++];
	output[i] = 0;
	return (output);
}
