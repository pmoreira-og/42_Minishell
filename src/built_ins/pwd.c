/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:02 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/24 11:50:32 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(void)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		perror("pwd");
		return (1);
	}
	ft_printf_fd(1, "%s\n", current);
	free(current);
	return (0);
}
