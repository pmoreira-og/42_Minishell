/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:50:57 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/04 12:28:58 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /// @brief Function to get a matrix of the enviroment variable.
// /// @param envp Enviroment.
// /// @param target Enviroment variable determinated.
// /// @param split Char to split into a matrix.
// /// @return A matrix null terminated. Each string terminated by /
// char	**ft_getenv(char **envp, char *target, char split)
// {
// 	char	**matrix;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	temp = NULL;
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], target, ft_strlen(target)))
// 			temp = envp[i] + (ft_strlen(target) + 1);
// 		i++;
// 	}
// 	matrix = ft_split((char *) temp, split);
// 	if (!matrix)
// 		return (NULL);
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		temp = matrix[i];
// 		matrix[i] = ft_strjoin(matrix[i], "/");
// 		free (temp);
// 		i++;
// 	}
// 	return (matrix);
// }

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

void	try_run(t_hell *data, char **args)
{
	char	*new_path;

	if (data && args && args[0])
	{
		new_path = path_handler(args[0]);
		if (!new_path)
			return (merror("try_run:new_path"));
		if (ft_strchr(new_path, '/') && access(new_path, F_OK) == -1)
		{
			ft_printf_fd(2, "minishell: %s: %s\n", args[0], strerror(errno));
			free(new_path);
			mini_cleaner(NULL, data, 127);
		}
		if (ft_strchr(new_path, '/') && access(new_path, X_OK) == -1)
		{
			ft_printf_fd(2, "minishell: %s: %s\n", args[0], strerror(errno));
			free(new_path);
			mini_cleaner(NULL, data, 126);
		}
		execve(new_path, args, data->envp);
		if (new_path)
			free(new_path);
		ft_printf_fd(2, "minishell: %s: command not found\n", args[0]);
		mini_cleaner(NULL, data, 127);
	}
}

int	update_fds(t_cmd *cmd)
{
	t_redirection	*in;
	t_redirection	*out;
	t_redirection	*temp;

	in = NULL;
	out = NULL;
	temp = cmd->redirs;
	while (temp)
	{
		if (temp->type == INFILE || temp->type == LIM)
			in = temp;
		if (temp->type == OUTFILE \
			|| temp->type == OUTFILE_APPEND)
			out = temp;
		temp = temp->next;
	}
	if (in && in->fd != -1)
		cmd->fd_in = dup(in->fd);
	if (out && out->fd != -1)
		cmd->fd_out = dup(out->fd);
	return (1);
}
