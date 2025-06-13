/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:50:57 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/13 14:24:41 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_clean_pipex(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->paths)
		ft_clean_matrix(pipex->paths);
	if (pipex->envp)
		pipex->envp = NULL;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[++i])
			ft_clean_matrix(pipex->cmd_args[i]);
		free(pipex->cmd_args);
	}
	if (pipex->childs)
		free(pipex->childs);
	if (pipex->out_fd > 0)
		close(pipex->out_fd);
	if (pipex->in_fd >= 0)
		close(pipex->in_fd);
	free(pipex);
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

int	ft_dup(t_pipex *pipex, int count)
{
	int	status;

	if (count == pipex->cmd_count - 1)
	{
		status = dup2(pipex->out_fd, 1);
		if (status < 0)
			return (0);
	}
	else
	{
		status = dup2(pipex->pipe[1], 1);
		if (status < 0)
			return (0);
		close(pipex->pipe[1]);
	}
	close(pipex->out_fd);
	return (status);
}

void	try_run(t_pipex *pipex, char **program)
{
	if (program[0])
	{
		if (access(program[0], F_OK) == -1)
		{
			perror("Command not found");
			ft_clean_pipex(pipex);
			exit(127);
		}
		if (access(program[0], X_OK) == -1)
		{
			perror("Error");
			ft_clean_pipex(pipex);
			exit(126);
		}
		execve(program[0], program, pipex->envp);
	}
}

void	ft_heredoc(t_pipex *pipex, /*const*/ char **av)
{
	char	*line;

	line = NULL;
	pipex->in_fd = open(av[1], O_RDWR | O_CREAT, 0766);
	if (pipex->in_fd < 0)
		return (perror("here_doc error"));
	while (1)
	{
		// line = get_next_line_fd(pipex->in_fd, 0, av);
		if (!line)
			break ;
		free(line);
	}
	close(pipex->in_fd);
	free(line);
}
