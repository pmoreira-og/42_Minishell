/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:58 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/23 12:11:58 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo
// echo arg
// echo flag + arg
// echo redirects (ver depois)

static int	ft_check_n(t_cmd cmd)
{
	int	i;

	i = 0;
	if (cmd.argv[1][i] == '-')
	{
		i++;
		while (cmd.argv[1][i] == 'n')
		{
			i++;
			if (!cmd.argv[1][i])
				return(1);
		}
	}
	return (0);
}

void	echo(t_cmd cmd)
{
	int	token;
	int	flag;

	flag = 0;
	token = 0;
	if (cmd.argv[1] == NULL || (cmd.argv[1][0] == '-' && ft_strlen(cmd.argv[1]) == 1))
		return((void)printf("\n"));
	if (ft_check_n(cmd))
	{
		token++;
		flag++;
	}
	while (cmd.argv[++token])
	{
		printf("%s", cmd.argv[token]);
		if (cmd.argv[token + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return ;
}
