/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:30:13 by pmoreira          #+#    #+#             */
/*   Updated: 2024/10/30 14:52:31 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	letter;

	str = (char *) s;
	letter = (unsigned char) c;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == letter)
			return (&str[i]);
		i++;
	}
	if (str[i] == letter)
		return (&str[i]);
	return (0);
}
