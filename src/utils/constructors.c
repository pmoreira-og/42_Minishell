/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:20 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/29 15:27:08 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hell	*init_hell(int ac, char **av,char **envp)
{
	t_hell	*hell;

	hell = ft_calloc(1, sizeof(t_hell));
	if (!hell)
		return (NULL);
	hell->tokens = ft_calloc(1, sizeof(t_token));
	if (!hell->tokens)
		return (free(hell), NULL);
	hell->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!hell->cmd)
		return (free(hell->tokens), free(hell), NULL);
	init_env(&hell->env, envp);
	hell->envp = envp;
	if (!get_history_fd(hell))
		load_history(hell);
	if (ac == 2 && !ft_strcmp(av[1], "-b"))
		printascii();
	hell->path = ft_getenv(envp, "PATH", ':');
	if (!hell->path)
		return (armageddon(hell), NULL);
	return (hell);
}
