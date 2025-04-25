/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:44 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/25 12:16:06 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_numcheck(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	mini_exit(t_hell *hell)
{
	if (hell->cmd->argv[1] && ft_numcheck(hell->cmd->argv[1]))
		hell->status = ft_atoi(hell->cmd->argv[1]);
	else if (hell->cmd->argv[1] && !ft_numcheck(hell->cmd->argv[1]))
		printf("-\033[1;31mMinishell$\033[0m: exit: %s: numeric argument required\n", hell->cmd->argv[1]);
	else if (hell->status)
		exit(hell->status);
	else
		exit(0);
}
