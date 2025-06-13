/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:06:08 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/12 15:04:52 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include <limits.h>

static void	ft_printhex(unsigned int nbr, char type, int fd)
{
	char	*base;

	if (type == 'x')
		base = "0123456789abcdef";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	if (nbr < 16)
		ft_putchar_fd(base[nbr], fd);
	else if (nbr >= 16)
	{
		ft_printhex((nbr / 16), type, fd);
		ft_printhex((nbr % 16), type, fd);
	}
}

int	ft_itoh_fd(unsigned int nbr, char type, int fd)
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
	ft_printhex(temp, type, fd);
	if (temp == 0)
		size = 1;
	return (size);
}
