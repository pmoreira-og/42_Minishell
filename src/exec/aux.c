/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:50:57 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/23 10:56:32 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	matrix = ft_split((char *) temp, split);
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

void	ft_clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/// @brief Dup2 the src fd to the dst fd and close dst.
t_bool	ft_dup(int dst, int src)
{
	if (dup2(dst, src) == -1)
		return (FALSE);
	close(dst);
	return (TRUE);
}

void	try_run(t_hell *data, char **program)
{
	if (data && program && program[0])
	{
		if (access(program[0], F_OK) == -1)
		{
			ft_printf_fd(2, "Command '%s' not found\n", program[0]);
			mini_cleaner(NULL, data, 127);
		}
		if (access(program[0], X_OK) == -1)
		{
			ft_printf_fd(2, "minishell: %s: Permission denied\n", program[0]);
			mini_cleaner(NULL, data, 126);
		}
		execve(program[0], program, data->envp);
	}
}
