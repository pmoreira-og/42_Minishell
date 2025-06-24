/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:18 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/24 10:50:40 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_hell *shell, t_cmd *cmd)
{
	t_env	*temp;

	temp = shell->env;
	while (temp)
	{
		ft_printf_fd(cmd->fd_out, "%s=", temp->var);
		if (temp->value)
			ft_printf_fd(cmd->fd_out, "%s\n", temp->value);
		else
			ft_printf_fd(cmd->fd_out, "\n");
		temp = temp->next;
	}
	return ;
}
