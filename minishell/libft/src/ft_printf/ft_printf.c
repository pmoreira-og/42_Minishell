/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:14:38 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/06 10:44:47 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	ft_inputtype(const char *s, va_list *item)
{
	if (*s == 'c')
		return (ft_putchar(va_arg (*item, int)));
	if (*s == 's')
		return (ft_putstr(va_arg(*item, char *)));
	if (*s == 'd' || *s == 'i')
		return (ft_printnbr(va_arg(*item, int)));
	if (*s == 'x')
		return (ft_itoh(va_arg(*item, unsigned int), 'x'));
	if (*s == 'X')
		return (ft_itoh(va_arg(*item, unsigned int), 'X'));
	if (*s == '%')
		return (ft_putchar('%'));
	if (*s == 'u')
		return (ft_printunbr(va_arg(*item, unsigned int)));
	if (*s == 'p')
		return (ft_printptr(va_arg(*item, unsigned long)));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		count;

	if (input == 0)
		return (-1);
	va_start (args, input);
	count = 0;
	while (*input)
	{
		if (*input == '%')
		{
			count += ft_inputtype(++input, &args);
			input++;
		}
		else
		{
			write(1, input, 1);
			input++;
			count++;
		}
	}
	va_end(args);
	return (count);
}
