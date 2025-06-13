/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:34:25 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/13 14:00:12 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include <limits.h>

static void	putnum_fd(unsigned int n, int fd)
{
	if (n == 0)
		ft_putchar_fd((n + '0'), fd);
	if (n > 0 && n <= 9)
	{
		ft_putchar_fd((n + '0'), fd);
	}
	else if (n > 9)
	{
		putnum_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
}

int	ft_printunbr_fd(unsigned int num, int fd)
{
	int	size;
	int	temp;

	size = 0;
	temp = num;
	while (num != 0)
	{
		size++;
		num /= 10;
	}
	putnum_fd(temp, fd);
	if (temp == 0 || temp < INT_MIN || temp > INT_MAX)
		size = 1;
	return (size);
}
