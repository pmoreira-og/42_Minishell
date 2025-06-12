/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:04 by ernda-si          #+#    #+#             */
/*   Updated: 2025/05/20 16:26:06 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dir_handler(t_env **env, char *path, char *c_path)
{
	ft_setenv(env, "OLDPWD", c_path);
	chdir(path);
}

void	mini_cd(t_cmd *cmd, t_env **env, t_hell *shell)
{
	char	*c_path;
	char	*n_path;

	c_path = getcwd(NULL, 0);
	if (cmd->argc > 2)
		return ((void)printf("minishell: cd: too many arguments\n"), \
			(void)(shell->status = 1));
	if (!cmd->args[1])
		dir_handler(env, getenv("HOME"), c_path);
	else if (!ft_strcmp(cmd->args[1], "/"))
		dir_handler(env, "/", c_path);
	if (cmd->args[1][0] == '~' && cmd->args[1][1] == '/')
	{
		n_path = ft_strjoin(getenv("HOME"), ft_strchr(cmd->args[1], '/'));
		printf("n_path: %s\n", n_path);
		dir_handler(env, n_path, c_path);
	}
	else if (cmd->args[1])
	{
		n_path = ft_strjoin(c_path, "/");
		n_path = ft_strjoin(n_path, cmd->args[1]);
		dir_handler(env, n_path, c_path);
	}
	n_path = getcwd(NULL, 0);
	ft_setenv(env, "PWD", n_path);
}
