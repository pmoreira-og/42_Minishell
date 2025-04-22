/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:31:27 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:20:45 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int num);
static int	ft_putnbr(char *str, int num);

static int	ft_putnbr(char *str, int num)
{
	*str = (num % 10) + '0';
	return (num /= 10);
}

static int	ft_size(int num)
{
	int	size;

	size = 0;
	if (num < 0)
		size++;
	while (num != 0)
	{
		size++;
		num /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	size = ft_size(n);
	str = (char *) malloc((size + 1) * sizeof(char));
	if (str == 0)
		return (0);
	str[size] = 0;
	if (n >= 0)
	{
		while (--size >= 0)
			n = ft_putnbr(&str[size], n);
	}
	else
	{
		n *= (-1);
		while (--size > 0)
			n = ft_putnbr(&str[size], n);
		str[size] = '-';
	}
	return (str);
}
