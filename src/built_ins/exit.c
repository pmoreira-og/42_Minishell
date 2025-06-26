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

static int	num_limit(char *str)
{
	int	is_neg;
	
	is_neg = (str[0] == '-');
	if (str[0] == '+' || str[0] == '-')
		str++;
	if (ft_strlen(str) > 19)
		return (0);
	if (ft_strlen(str) == 19)
	{
		if (!is_neg && ft_strcmp(str, "9223372036854775807") > 0)
			return (0);
		if (is_neg && ft_strcmp(str, "9223372036854775808") > 0)
			return (0);
	}
	return (1);
}

static int	is_valid_numeric_arg(char *arg)
{
	int	i;
	int	has_sign;

	i = 0;
	has_sign = (arg[i] == '-' || arg[i] == '+');
	if (has_sign)
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (num_limit(arg));
}

int	first_check(char *arg)
{
	char	**matrix;
	int		result;

	matrix = ft_params(arg);
	if (!matrix)
		return (0);
	if (matrix[1])
		return (ft_clean_matrix(matrix), 0);
	result = is_valid_numeric_arg(matrix[0]);
	ft_clean_matrix(matrix);
	return (result);
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
