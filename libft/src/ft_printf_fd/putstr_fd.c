/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:19:24 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/12 14:46:33 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	putstr_fd(char *s, int fd)
{
	int	size;

	if (!s)
		s = "(null)";
	size = 0;
	while (s[size])
		size++;
	return (write(fd, s, size));
}
