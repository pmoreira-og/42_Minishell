/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:08:02 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:21:25 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	is_upper;
	int	is_lower;
	int	is_digit;
	int	is_alpha;

	is_upper = (c >= 'A' && c <= 'Z');
	is_lower = (c >= 'a' && c <= 'z');
	is_digit = (c >= '0' && c <= '9');
	is_alpha = (is_upper || is_lower);
	return (is_alpha || is_digit);
}
