/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:02 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/30 14:44:49 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(void)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		ft_printf_fd(1, "%s\n", get_env(&get_hell(NULL)->env, "PWD"));
		return (0);
	}
	ft_printf_fd(1, "%s\n", current);
	free(current);
	return (0);
}
