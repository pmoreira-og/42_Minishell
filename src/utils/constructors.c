/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:20 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/29 10:11:58 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hell	*init_hell(int ac, char **av,char **envp)
{
	t_hell	*hell;

	hell = ft_calloc(1, sizeof(t_hell));
	if (!hell)
		return (NULL);
	init_env(&hell->env, envp);
	init_export(&hell->export, envp);
	hell->envp = envp;
	if (!get_history_fd(hell))
		load_history(hell);
	if (ac == 2 && !ft_strcmp(av[1], "-b"))
		printascii();
	if (ac == 2 && !ft_strcmp(av[1], "-d"))
		hell->debug = TRUE;
	hell->path = ft_getenv(envp, "PATH", ':');
	if (!hell->path)
		return (armageddon(hell), NULL);
	return (hell);
}
