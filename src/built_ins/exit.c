/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:15:44 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/25 16:18:22 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// arg > 1 n sai , status = 1, printa exit anyway, printa erro "bash: exit: too many arguments"
// arg value > 255 status vira 0
// arg value < 0 ele soma com 256
// arg value < 0 e < -255
// letter check status == 2
// 9223372036854775807 long max size == 19 | -9223372036854775808 long min size == 20

static int	first_check(char *arg)
{
	char	**matrix;
	int		flag;
	int		i;

	i = 0;
	matrix = ft_params(arg);
	if (!matrix)
		return (0);
	if (matrix[1])
		return (ft_clean_matrix(matrix), 0);
	flag = matrix[0][i] == '-' || matrix[0][i] == '+';
	if (flag)
		i++;
	while (matrix[0][i])
	{
		if (!ft_isdigit(matrix[0][i]))
			return (ft_clean_matrix(matrix), 0);
		i++;
	}
	if (!matrix[0][i])
		i--;
	if (i > (19 + flag))
		return (ft_clean_matrix(matrix), 0);
	return (ft_clean_matrix(matrix), 1);
}

int	mini_exit(t_hell *hell, t_cmd *cmd)
{
	if (!cmd->prev)
		ft_printf_fd(1, "exit\n");
	if (cmd->argc == 1)
		mini_cleaner(NULL, hell, hell->status);
	if (!cmd->prev && cmd->argc > 2)
		return (ft_printf_fd(1, "minishell: exit: too many arguments\n"), 1);
	if (!cmd->prev && !first_check(cmd->args[1]))
	{
		ft_printf_fd(1, "minishell: exit: %s: numeric argument required\n", \
			cmd->args[1]);
		mini_cleaner(NULL, hell, 2);
	}
	mini_cleaner(NULL, hell, (unsigned char)ft_strtol(cmd->args[1], NULL, 10));
	return 1;
}
