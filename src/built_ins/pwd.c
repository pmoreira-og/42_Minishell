/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:02 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/13 14:10:27 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(t_cmd *cmd)
{
	char	*current;

	(void)cmd;
	current = getcwd(NULL, 0);
	if (!current)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", current);
	free(current);
	return (0);
}
