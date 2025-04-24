/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:04 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/24 14:11:22 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// dd para double dots btw, n pensei em nome melhor ent se quiser mudar va em frentekkkk
/* static void	dd_handler(char *path)
{

} */

/* static int	dd_check(char *path)
{
	char	**dirs;
	int		i;

	i = 0;
	dirs = ft_split(path, '/');
	while (dirs[i] && ft_strcmp(dirs[i], ".."))
	{
		i++;
		if (!dirs[i])
			return(0);
	}
	return (1);
} */

void	cd(t_cmd cmd)
{
	// char	*c_path;
	// char	*n_path;

	(void)cmd;
	// c_path = getcwd(NULL, 0);
	if (cmd.argc > 2)
		exit(1);
	if (!cmd.argv[1])
		chdir(getenv("HOME"));
	else if (!ft_strcmp(cmd.argv[1], "/"))
		chdir("/");

/* 	else if (cmd.argv[1])
	{
		if (dd_check(cmd.argv[1]))
			printf("..");
		n_path = ft_strjoin(c_path, "/");
		n_path = ft_strjoin(n_path, cmd.argv[1]);
		chdir(n_path);
	} */
}
