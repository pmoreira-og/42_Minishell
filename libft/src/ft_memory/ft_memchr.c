/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:34:40 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:19:50 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	cbyte;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	cbyte = (unsigned char ) c;
	while (i < n)
	{
		if (str[i] == cbyte)
			return (&str[i]);
		i++;
	}
	return (0);
}
