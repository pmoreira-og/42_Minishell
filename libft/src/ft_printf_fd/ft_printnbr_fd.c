/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:55:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/12 15:04:02 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include <limits.h>

static void	putnbr_fd(unsigned int n, int fd)
{
	if (n == 0)
		ft_putchar_fd((n + '0'), fd);
	if (n > 0 && n <= 9)
	{
		ft_putchar_fd((n + '0'), fd);
	}
	else if (n > 9)
	{
		putnbr_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
}

int		ft_printnbr_fd(int num, int fd)
{
	int	size;
	int	temp;

	size = 0;
	temp = num;
	if (num < 0)
		size++;
	while (num != 0)
	{
		size++;
		num /= 10;
	}
	putnbr_fd(temp, fd);
	if (temp == 0 || temp < INT_MIN || temp > INT_MAX)
		size = 1;
	return (size);
}
