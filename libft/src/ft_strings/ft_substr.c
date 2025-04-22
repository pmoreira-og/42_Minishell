/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:46:23 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:16:51 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dup;
	size_t			i;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dup = (char *) malloc(len * sizeof(char) + 1);
	if (dup == 0)
		return (0);
	i = 0;
	while (i < len && s[start] != 0)
		dup[i++] = s[start++];
	dup[i] = '\0';
	return (dup);
}
