/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:47:26 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/13 13:59:58 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include "ft_fds.h"

static void	ft_printhex_fd(unsigned long nbr, char type, int fd)
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
		ft_printhex_fd((nbr / 16), type, fd);
		ft_printhex_fd((nbr % 16), type, fd);
	}
}

int	ft_printptr_fd(unsigned long ptr, int fd)
{
	int				size;
	unsigned long	temp;

	if (ptr == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	size = 0;
	temp = ptr;
	while (ptr > 0)
	{
		ptr /= 16;
		size++;
	}
	write(fd, "0x", 2);
	size += 2;
	ft_printhex_fd(temp, 'x', fd);
	return (size);
}
