/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:04 by ernda-si          #+#    #+#             */
/*   Updated: 2025/07/02 11:20:54 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_path(const char *path)
{
	int	i;
	int	j;

	if (!path)
		return (0);
	i = 0;
	j = 0;
	while (path[i])
	{
		if (!ft_strchr("/.", path[i]) || j > 2)
			return (0);
		if (path[i] == '/')
			j = 0;
		if (path[i] == '.')
			j++;
		i++;
	}
	return (1);
}

static void	update_env_pwd(t_env **env, char *oldpwd, char *pwd)
{
	if (!oldpwd)
		oldpwd = get_env(env, "PWD");
	ft_setenv(env, "OLDPWD", oldpwd);
	ft_setexport(&get_hell(NULL)->export, "OLDPWD", oldpwd);
	if (pwd)
		ft_setenv(env, "PWD", pwd);
	ft_setexport(&get_hell(NULL)->export, "PWD", pwd);
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

static void	normi_handler(char *c_path, char *n_path, t_env **env)
{
	char	*new_path;
	char	*temp;

	new_path = getcwd(NULL, 0);
	temp = NULL;
	if (!new_path && check_n_path(n_path))
	{
		temp = ft_expand(temp, get_env(env, "PWD"), NULL);
		temp = ft_expand(temp, "/", NULL);
		temp = ft_expand(temp, n_path, NULL);
		new_path = ft_expand(new_path, temp, &temp);
	}
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
	if (!(access(n_path, F_OK | X_OK) == 0))
		return (ft_printf_fd(2, \
			"minishell: cd: %s: No such file or directory\n", n_path), \
			free(n_path), free(c_path), 1);
	else if (chdir(n_path) == -1)
		return (perror("minishell: cd"), 1);
	else
		normi_handler(c_path, n_path, env);
	return (free(n_path), free(c_path), 0);
}
