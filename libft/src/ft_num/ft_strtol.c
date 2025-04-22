/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:26:27 by pmoreira          #+#    #+#             */
/*   Updated: 2025/03/14 16:25:03 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(int base, const char **s)
{
	if (base == 0)
	{
		if (*(*s) == '0')
		{
			if ((*s)[1] == 'x' || (*s)[1] == 'X')
			{
				base = 16;
				*s += 2;
			}
			else
			{
				base = 8;
				*s += 1;
			}
		}
		else
			base = 10;
	}
	else if (base == 16 && **s == '0' && ((*s)[1] == 'x' || (*s)[1] == 'X'))
		*s += 2;
	return (base);
}

static int	get_digit(const char *s, int *digit, int base)
{
	if (ft_isdigit((unsigned char)*s))
		*digit = *s - '0';
	else if (ft_isalpha((unsigned char)*s))
		*digit = ft_tolower((unsigned char)*s) - 'a' + 10;
	else
		return (0);
	if (*digit >= base)
		return (0);
	return (1);
}

static int	check_overflow(long int *result, int digit, int base, int sign)
{
	if (*result > (LONG_MAX - digit) / base)
	{
		if (sign == 1)
			*result = LONG_MAX;
		else
			*result = LONG_MIN;
		return (1);
	}
	*result = *result * base + digit;
	return (0);
}

static void	check_signal(int *sign, const char	**s)
{
	if (*(*s) == '+')
		(*s) += 1;
	else if (*(*s) == '-')
	{
		*sign = -1;
		(*s) += 1;
	}
}

/// @brief Function implemented to reproduce the behavior of the strtol
/// function, but does not handle errno.
/// @param str String to be converted.
/// @param endptr Address of the pointer where the conversion ended.
/// If not desired, provide NULL as a parameter.
/// @param base Base chosen for conversion.
/// @return Conversion result. In case of error:
/// LONG_MAX for overflow or LONG_MIN for underflow.
long int	ft_strtol(const char *str, char **endptr, int base)
{
	const char	*s;
	long int	result;
	int			sign;
	int			digit;

	s = str;
	result = 0;
	sign = 1;
	while (ft_isspace((unsigned char)*s))
		s++;
	check_signal(&sign, &s);
	base = check_base(base, &s);
	while (*s)
	{
		if (!get_digit(s, &digit, base))
			break ;
		if (check_overflow(&result, digit, base, sign))
			break ;
		s++;
	}
	if (endptr != NULL)
		*endptr = (char *)s;
	return (result * sign);
}
