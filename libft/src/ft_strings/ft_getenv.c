/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:41:18 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/04 12:31:48 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*find_target(char **envp, char *target)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (envp && envp[i])
	{
		if (ft_strnstr(envp[i], target, ft_strlen(target)))
			temp = envp[i] + (ft_strlen(target) + 1);
		i++;
	}
	return (temp);
}

int	concat_tab(char **matrix)
{
	int		i;
	char	*temp;

	if (!matrix)
		return (1);
	i = 0;
	temp = NULL;
	while (matrix[i])
	{
		temp = matrix[i];
		matrix[i] = ft_strjoin(matrix[i], "/");
		if (!matrix[i])
			return (ft_free(matrix, ++i), 0);
		free(temp);
		i++;
	}
	return (1);
}

/// @brief Function to get a matrix of the enviroment variable.
/// @param envp Enviroment.
/// @param target Enviroment variable determinated.
/// @param split Char to split into a matrix.
/// @param flag Int to save malloc fail status.
/// @return A matrix null terminated. Each string terminated by /
char	**ft_getenv(char **envp, char *target, char split, int *flag)
{
	char	**matrix;
	char	*temp;

	temp = find_target(envp, target);
	matrix = ft_split((const char *) temp, split);
	if (!matrix)
		return (NULL);
	if (!concat_tab(matrix))
	{
		if (flag)
			*flag = 1;
		return (NULL);
	}
	return (matrix);
}
