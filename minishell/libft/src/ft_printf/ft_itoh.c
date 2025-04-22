/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:06:08 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/07 10:41:55 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

static void	ft_printhex(unsigned int nbr, char type)
{
	char	*base;

	if (type == 'x')
		base = "0123456789abcdef";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	if (nbr < 16)
		ft_putchar(base[nbr]);
	else if (nbr >= 16)
	{
		ft_printhex((nbr / 16), type);
		ft_printhex((nbr % 16), type);
	}
}

int	ft_itoh(unsigned int nbr, char type)
{
	int				size;
	unsigned int	temp;

	size = 0;
	temp = nbr;
	while (nbr > 0)
	{
		nbr /= 16;
		size++;
	}
	ft_printhex(temp, type);
	if (temp == 0)
		size = 1;
	return (size);
}
