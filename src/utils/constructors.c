/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:20 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/02 11:48:57 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_local_envp(void)
{
	char	**new_envp;

	new_envp = ft_params("SHLVL=1");
	if (!new_envp)
		return (NULL);
	print_matrix(new_envp);
	return (new_envp);
}

t_hell	*init_hell(int ac, char **av,char **envp)
{
	t_hell	*hell;
	char	**new_envp;

	hell = ft_calloc(1, sizeof(t_hell));
	if (!hell)
		return (NULL);
	if (!envp)
		new_envp = init_local_envp();
	else
		new_envp = envp;
	init_env(&hell->env, new_envp);
	init_export(&hell->export, new_envp);
	if (!hell->env || !hell->export)
		return (armageddon(hell), NULL);
	hell->envp = new_envp;
	hell->path = ft_getenv(new_envp, "PATH", ':');
	if (!hell->path)
		return (armageddon(hell), NULL);
	if (!get_history_fd(hell))
		load_history(hell);
	if (ac == 2 && !ft_strcmp(av[1], "-b"))
		printascii();
	if (ac == 2 && !ft_strcmp(av[1], "-d"))
		hell->debug = TRUE;
	return (hell);
}
