/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:12:02 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/23 12:12:02 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <unistd.h>

void	pwd(t_cmd cmd)
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
