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

static int	check_dir(const char *path)
{
	return (access(path, F_OK | X_OK) == 0);
}

static void	update_env(t_env **env, char *oldpwd, char *pwd)
{
	ft_setenv(env, "OLDPWD", oldpwd);
	ft_setenv(env, "PWD", pwd);
}

static char	*path_handler(char *arg)
{
	char	*home;

	if (!arg || ft_strcmp(arg, "~") == 0)
	{
		home = getenv( "HOME");
		if (home)
			return (ft_strdup(home));
		else
			return (NULL);
	}
	if (ft_strncmp(arg, "~/", 2) == 0)
	{
		home = getenv("HOME");
		if (!home)
			return (NULL);
		return (ft_strjoin(ft_strdup(home), ft_strchr(arg, '/')));
	}
	return (ft_strdup(arg));
}

void	mini_cd(t_cmd *cmd, t_env **env, t_hell *shell)
{
	char	*c_path;
	char	*n_path;
	char	*new_path;

	c_path = getcwd(NULL, 0);
	if (!c_path)
		return ((void)(perror("minishell: cd"), shell->status = 1));
	if (cmd->argc > 2)
		return ((void)printf("minishell: cd: too many arguments\n"), \
			(void)(shell->status = 1), free(c_path));
	n_path = path_handler(cmd->args[1]);
	if (!n_path)
		return ((void)printf("minishell: cd: HOME not set\n"), \
			(void)(shell->status = 1), free(c_path));
	if (!check_dir(n_path))
	{
		printf("minishell: cd: %s: No such file or directory\n", n_path);
		shell->status = 1;
	}
	else if (chdir(n_path) == -1)
	{
		perror("minishell: cd");
		shell->status = 1;
	}
	else
	{
		new_path = getcwd(NULL, 0);
		if (new_path)
		{
			update_env(env, c_path, new_path);
			free(new_path);
		}
		shell->status = 0;
	}
	free(n_path);
	free(c_path);
}
