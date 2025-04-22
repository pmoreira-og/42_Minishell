/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:34:25 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/07 10:54:53 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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

int	ft_printunbr(unsigned int num)
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
	ft_putnbr(temp);
	if (temp == 0 || temp < INT_MIN || temp > INT_MAX)
		size = 1;
	return (size);
}
