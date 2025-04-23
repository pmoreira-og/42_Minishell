/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:04 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/23 13:37:32 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	cd(t_cmd cmd)
{
	char	*c_path;
	char	*n_path;

	(void)cmd;
	c_path = getcwd(NULL, 0);
	if (cmd.argc > 2)
		exit(1);
	if (!cmd.argv[1])
		chdir(getenv("HOME"));
	else if (!ft_strcmp(cmd.argv[1], "/"))
		chdir("/");
	else if (cmd.argv[1])
	{
		n_path = ft_strjoin(c_path, "/");
		n_path = ft_strjoin(n_path, cmd.argv[1]);
		chdir(n_path);
	}
}
