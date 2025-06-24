/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:58 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/24 10:33:40 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	mini_echo(t_cmd *cmd)
{
	int	i;
	int	no_newline;

	no_newline = 0;
	i = 1;
	while (cmd->args[i] && is_flag_n(cmd->args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_printf_fd(cmd->fd_out, "%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf_fd(cmd->fd_out, " ");
		i++;
	}
	if (!no_newline)
		ft_printf_fd(cmd->fd_out, "\n");
	return (0);
}
