/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:04 by ernda-si          #+#    #+#             */
/*   Updated: 2025/07/02 09:58:08 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dir(const char *path)
{
	return (access(path, F_OK | X_OK) == 0);
}

static void	update_env_pwd(t_env **env, char *oldpwd, char *pwd)
{
	ft_setenv(env, "OLDPWD", oldpwd);
	ft_setenv(env, "PWD", pwd);
}

char	*path_handler(char *arg)
{
	char	*home;

	if (!arg || ft_strcmp(arg, "~") == 0)
	{
		home = getenv("HOME");
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
		return (ft_strjoin(home, ft_strchr(arg, '/')));
	}
	return (ft_strdup(arg));
}

static void	normi_handler(char *c_path, t_env **env)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	if (new_path)
		(update_env_pwd(env, c_path, new_path), free(new_path));
	get_hell(NULL)->status = 0;
}

int	mini_cd(t_cmd *cmd, t_env **env)
{
	char	*c_path;
	char	*n_path;

	c_path = getcwd(NULL, 0);
	if (cmd->argc > 2)
		return (ft_printf_fd(2, "minishell: cd: too many arguments\n"), \
			free(c_path), 1);
	n_path = path_handler(cmd->args[1]);
	if (!n_path)
		return (ft_printf_fd(2, "minishell: cd: HOME not set\n"), \
			free(c_path), 1);
	if (!check_dir(n_path))
		return (ft_printf_fd(2, \
			"minishell: cd: %s: No such file or directory\n", n_path), \
			free(n_path), free(c_path), 1);
	else if (chdir(n_path) == -1)
		return (perror("minishell: cd"), 1);
	else
		normi_handler(c_path, env);
	return (free(n_path), free(c_path), 0);
}
