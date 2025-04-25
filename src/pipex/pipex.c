/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:39:39 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/24 14:54:05 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_and_close(int dst, int src)
{
	dup2(dst, src);
	close(dst);
}

void	is_exec(t_pipex *pipex, char **program)
{
	char	**av;
	char	*temp;

	av = ft_getenv(pipex->envp, "HOME", '0');
	if (program[0][0] == '~' && program[0][1] == '/' && av)
	{
		temp = program[0];
		program[0] = ft_strjoin(av[0], program[0] + 2);
		free(temp);
		ft_clean_matrix(av);
		execve(program[0], program, pipex->envp);
	}
	if (av)
		ft_clean_matrix(av);
	return (try_run(pipex, program));
}

void	child(t_pipex *pipex, char **program, int count)
{
	int		i;
	char	*temp;

	i = 0;
	if (!program)
		return (ft_clean_pipex(pipex), exit(127));
	close(pipex->pipe[0]);
	close(pipex->in_fd);
	ft_dup(pipex, count);
	while (pipex->paths && pipex->paths[i])
	{
		temp = ft_strjoin((const char *) pipex->paths[i] \
		, (const char *) program[0]);
		execve(temp, program, pipex->envp);
		free(temp);
		i++;
	}
	is_exec(pipex, program);
}

void	parent(t_pipex *pipex, int count)
{
	int	pid;

	if (count != pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipe) < 0)
			return (perror("pipe error"));
	}
	pid = fork();
	if (pid < 0)
		return (perror("PID error"));
	pipex->childs[count] = pid;
	if (pid == 0)
		child(pipex, pipex->cmd_args[count], count);
	else
	{
		close(pipex->pipe[1]);
		dup2(pipex->pipe[0], 0);
		close(pipex->pipe[0]);
	}
}

int	pipex(int ac, char const **av, char *envp[])
{
	int		i;
	t_pipex	*pipex;

	if (!envp || !*envp)
		return (ft_putstr_fd("Invalid path\n", 2), 1);
	if (ac < 5 || (!ft_strcmp(av[1], "here_doc") && ac < 6))
		return (ft_putstr_fd("Invalid input\n", 2), 0);
	pipex = ft_init_struct(envp, ac - 2, av);
	if (!pipex)
		return (ft_putstr_fd("Unable to generate a valid structure\n", 2), 1);
	if (!check_files(ac, av, pipex))
		return (ft_clean_pipex(pipex), 1);
	dup_and_close(pipex->in_fd, 0);
	i = -1;
	while (++i < pipex->cmd_count)
		parent(pipex, i);
	close(0);
	if (pipex->here_doc)
		unlink(av[1]);
	i = wait_childs(pipex);
	ft_clean_pipex(pipex);
	return (i);
}
