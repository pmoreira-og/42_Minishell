/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:40:48 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:19:31 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*sc;

	if (dest == 0 && src == 0)
		return (0);
	if (dest <= src)
		return (ft_memcpy(dest, src, n));
	else if (dest > src)
	{
		dt = (unsigned char *) dest;
		sc = (const unsigned char *) src;
		dt += n - 1;
		sc += n - 1;
		while (n--)
		{
			*dt-- = *sc--;
		}
	}
	return (dest);
}
