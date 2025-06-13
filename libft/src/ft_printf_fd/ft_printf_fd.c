/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:14:38 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/12 15:03:39 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include <stdarg.h>

static int	ft_inputtype_fd(const char *s, va_list *item, int fd)
{
	if (*s == 'c')
		return (ft_putchar_fd(va_arg (*item, int), fd), 1);
	if (*s == 's')
		return (putstr_fd(va_arg(*item, char *), fd));
	if (*s == 'd' || *s == 'i')
		return (ft_printnbr_fd(va_arg(*item, int), fd));
	if (*s == 'x')
		return (ft_itoh_fd(va_arg(*item, unsigned int), 'x', fd));
	if (*s == 'X')
		return (ft_itoh_fd(va_arg(*item, unsigned int), 'X', fd));
	if (*s == '%')
		return (ft_putchar_fd('%', fd), 1);
	if (*s == 'u')
		return (ft_printunbr_fd(va_arg(*item, unsigned int), fd));
	if (*s == 'p')
		return (ft_printptr_fd(va_arg(*item, unsigned long), fd));
	return (0);
}
int		ft_printf_fd(int fd, const char *input, ...)
{
	va_list	args;
	int		count;

	if (input == 0)
		return (-1);
	va_start (args, input);
	count = 0;
	while (*input)
	{
		if (*input == '%' && *(input + 1))
		{
			count += ft_inputtype_fd(++input, &args, fd);
			input++;
		}
		else
		{
			write(fd, input, 1);
			input++;
			count++;
		}
	}
	va_end(args);
	return (count);
}
