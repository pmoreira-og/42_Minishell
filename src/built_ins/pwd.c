/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:02 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/25 12:13:53 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(t_cmd *cmd)
{
	char *current;

	(void)cmd;
	current = getcwd(NULL, 0);
	if (!current)
		printf("Error 'pwd'\n");
	printf("%s\n", current);
	free(current);
	return ;
}
