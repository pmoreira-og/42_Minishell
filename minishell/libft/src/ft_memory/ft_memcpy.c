/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:26:42 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:19:36 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*sc;
	size_t				i;

	if (dest == 0 && src == 0)
		return (0);
	dt = (unsigned char *) dest;
	sc = (const unsigned char *) src;
	i = 0;
	while (i < n)
	{
		dt[i] = sc[i];
		i++;
	}
	return (dest);
}
