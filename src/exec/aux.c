/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:50:57 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/24 12:29:42 by pmoreira         ###   ########.fr       */
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
	if (src == -1)
		return (FALSE);
	if (dup2(dst, src) == -1)
		return (FALSE);
	return (TRUE);
}

void	try_run(t_hell *data, char **program)
{
	char	*new_path;

	if (data && program && program[0])
	{
		new_path = path_handler(program[0]);
		if (!new_path)
			return (merror("try_run:new_path"));
		if (access(new_path, F_OK) == -1)
		{
			ft_printf_fd(2, "Command '%s' not found\n", program[0]);
			free(new_path);
			mini_cleaner(NULL, data, 127);
		}
		if (access(new_path, X_OK) == -1)
		{
			printf("%s\n", new_path);
			ft_printf_fd(2, "minishell: %s: Permission denied\n", program[0]);
			free(new_path);
			mini_cleaner(NULL, data, 126);
		}
		execve(new_path, program, data->envp);
	}
}

int	update_fds(t_cmd *cmd)
{
	t_redirection	*in;
	t_redirection	*out;

	in = cmd->redir_in;
	out = cmd->redir_out;
	while (in)
	{
		if (!in->next)
			cmd->fd_in = dup(in->fd);
		if (in->fd != -1)
			close(in->fd);
		in = in->next;
	}
	while (out)
	{
		if (!out->next)
			cmd->fd_out = dup(out->fd);
		if (out->fd != -1)
			close(out->fd);
		out = out->next;
	}
	return (1);
}
