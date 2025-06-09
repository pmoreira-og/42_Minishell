/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:20 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/09 14:00:50 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_local_envp(t_hell *hell)
{
	char	**new_envp;
	char	*temp;

	new_envp = ft_calloc(sizeof(char *), 3);
	if (!new_envp)
		return (NULL);
	new_envp[0] = ft_strdup("PWD=");
	if (!new_envp[0])
		return (ft_clean_matrix(new_envp), merror("init_local_envp"), NULL);
	temp = getcwd(NULL, 0);
	if (!temp)
		return (ft_clean_matrix(new_envp), merror("init_local_envp"), NULL);
	new_envp[0] = ft_expand(new_envp[0], temp, &temp);
	if (!new_envp[0])
		return (ft_clean_matrix(new_envp), merror("init_local_envp"), NULL);
	new_envp[1] = ft_strdup("SHLVL=1");
	if (!new_envp[1])
		return (ft_clean_matrix(new_envp), merror("init_local_envp"), NULL);
	hell->no_env = TRUE;
	return (new_envp);
}

t_hell	*init_hell(int ac, char **av, char **envp)
{
	t_hell	*hell;
	char	**new_envp;

	hell = ft_calloc(1, sizeof(t_hell));
	if (!hell)
		return (merror("init_hell:main"), NULL);
	if (!envp || !ft_getenv(envp, "SHLVL", '\0'))
		new_envp = init_local_envp(hell);
	else
		new_envp = envp;
	init_env(&hell->env, new_envp);
	init_export(&hell->export, new_envp);
	if (!hell->env || !hell->export)
		return (merror("init_hell:env"), armageddon(hell), NULL);
	hell->envp = new_envp;
	hell->path = ft_getenv(new_envp, "PATH", ':');
	// if (!hell->path)
	// 	return (merror("init_hell:path"), armageddon(hell), NULL);
	if (!get_history_fd(hell))
		load_history(hell);
	if (ac == 2 && !ft_strcmp(av[1], "-b"))
		printascii();
	if (ac == 2 && !ft_strcmp(av[1], "-d"))
		hell->debug = TRUE;
	return (hell);
}
