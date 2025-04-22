/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:55:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/06 10:53:06 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_fds.h"
#include <limits.h>

static void	ft_putnbr(unsigned int n)
{
	if (n == 0)
		ft_putchar((n + '0'));
	if (n > 0 && n <= 9)
	{
		ft_putchar((n + '0'));
	}
	else if (n > 9)
	{
		ft_putnbr((n / 10));
		ft_putchar(((n % 10) + '0'));
	}
}

int	ft_printnbr(int num)
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
	ft_putnbr(temp);
	if (temp == 0 || temp < INT_MIN || temp > INT_MAX)
		size = 1;
	return (size);
}
