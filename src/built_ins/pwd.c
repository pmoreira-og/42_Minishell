/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:02 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/24 10:41:43 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(t_cmd *cmd)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		perror("pwd");
		return (1);
	}
	ft_printf_fd(cmd->fd_out, "%s\n", current);
	free(current);
	return (0);
}
