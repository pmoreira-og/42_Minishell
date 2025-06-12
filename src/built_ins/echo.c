/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:58 by ernda-si          #+#    #+#             */
/*   Updated: 2025/05/27 12:24:08 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <uchar.h>

static int	is_flag_n(char *arg)
{
	int i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	mini_echo(t_cmd *cmd, t_env **env, t_hell *shell)
{
	int	i;
	int	no_newline;

	(void)env;
	(void)shell;
	no_newline = 0;
	i = 1;

	while (cmd->args[i] && is_flag_n(cmd->args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!no_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
