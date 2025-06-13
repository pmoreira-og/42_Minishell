/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:11:31 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/04 15:28:29 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/include/libft.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		here_doc;
	int		pipe[2];
	int		cmd_count;
	int		*childs;
	char	**paths;
	char	**envp;
	char	***cmd_args;
}	t_pipex;

// int		pipex(int ac, char **av, char *envp[], t_hell *hell);

void	ft_exec(char **path, char **program);
// void	child(t_pipex *pipex, char **program, int count, t_hell *hell);
// void	parent(t_pipex *pipex, int count, t_hell *hell);
char	**ft_parse(char *s, char c);

// UTILS

int		check_files(int ac, char **av, t_pipex *pipex);
// t_pipex	*ft_init_struct(char *envp[], int size, char **av, t_hell *hell);
char	*get_next_line_fd(int dst, int src, char *limiter);
int		wait_childs(t_pipex *pipex);
char	**ft_getenv(char **envp, char *target, char split);

// AUXS

int		ft_dup(t_pipex *pipex, int count);
void	ft_clean_matrix(char **matrix);
void	ft_clean_pipex(t_pipex *pipex);
void	try_run(t_pipex *pipex, char **program);
void	ft_heredoc(t_pipex *pipex, char **av);

#endif