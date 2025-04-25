/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:04 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/25 12:14:18 by pmoreira         ###   ########.fr       */
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

static void	dir_handler(t_env *env, char *path, char *c_path)
{
	ft_setenv(&env, "OLDPWD", c_path);
	chdir(path);
}

void	mini_cd(t_cmd *cmd, t_env *env)
{
	char	*c_path;
	char	*n_path;

	c_path = getcwd(NULL, 0);
	if (cmd->argc > 2)
		exit(1);
	if (!cmd->argv[1])
		dir_handler(env, getenv("HOME"), c_path);
	else if (!ft_strcmp(cmd->argv[1], "/"))
		dir_handler(env, "/", c_path);
	if (cmd->argv[1][0] == '~' && cmd->argv[1][1] == '/')
	{
		n_path = ft_strjoin(getenv("HOME"), ft_strchr(cmd->argv[1], '/'));
		printf("n_path: %s\n", n_path);
		dir_handler(env, n_path, c_path);
	}
	else if (cmd->argv[1])
	{
		n_path = ft_strjoin(c_path, "/");
		n_path = ft_strjoin(n_path, cmd->argv[1]);
		dir_handler(env, n_path, c_path);
	}
	n_path = getcwd(NULL, 0);
	ft_setenv(&env, "PWD", n_path);
}
