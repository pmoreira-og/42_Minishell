/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:55:04 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:17:26 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	if (s1 == 0)
		return (ft_strdup(s2));
	if (s2 == 0)
		return (ft_strdup(s1));
	join = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) * sizeof(char)) + 1);
	if (join == 0)
		return (0);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(&join[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	return (join);
}
