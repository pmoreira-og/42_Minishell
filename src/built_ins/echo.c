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

// echo
// echo arg
// echo flag + arg
// echo redirects (ver depois)

static int	ft_check_n(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1][i] == '-')
	{
		i++;
		while (cmd->args[1][i] == 'n')
		{
			i++;
			if (!cmd->args[1][i])
				return(1);
		}
	}
	return (0);
}

void	mini_echo(t_cmd *cmd, t_env **env)
{
	int	token;
	int	flag;

	flag = 0;
	token = 0;
	(void) env;
	if (cmd->args[1] == NULL)
		return ((void)printf("\n"));
	if (ft_check_n(cmd))
	{
		token++;
		flag++;
	}
	while (cmd->args[++token])
	{
		printf("%s", cmd->args[token]);
		if (cmd->args[token + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return ;
}
