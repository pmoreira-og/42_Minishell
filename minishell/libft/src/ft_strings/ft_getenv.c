/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:41:18 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/15 09:42:01 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Function to get a matrix of the enviroment variable.
/// @param envp Enviroment.
/// @param target Enviroment variable determinated.
/// @param split Char to split into a matrix.
/// @return A matrix null terminated. Each string terminated by /
char	**ft_getenv(char **envp, char *target, char split)
{
	char	**matrix;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], target, ft_strlen(target)))
			temp = envp[i] + (ft_strlen(target) + 1);
		i++;
	}
	matrix = ft_split((const char *) temp, split);
	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		temp = matrix[i];
		matrix[i] = ft_strjoin(matrix[i], "/");
		free (temp);
		i++;
	}
	return (matrix);
}
