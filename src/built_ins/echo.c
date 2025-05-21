/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:58 by ernda-si          #+#    #+#             */
/*   Updated: 2025/05/20 16:26:34 by pmoreira         ###   ########.fr       */
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

static int	has_var(t_env **env, char *str)
{
	char	*env_var;
	t_env	*temp;

	temp = *env;
	env_var = ft_strchr(str, '$');
	if (!env_var)
		return(0);
	while (temp && ft_strcmp(env_var + 1, temp->var))
		temp = temp->next;
	if (!temp)
		return(2);
	return(1);
}

void	mini_echo(t_cmd *cmd, t_env **env)
{
	int	token;
	int	flag;

	flag = 0;
	token = 0;
	if (cmd->args[1] == NULL)
		return((void)printf("\n"));
	if (ft_check_n(cmd))
	{
		token++;
		flag++;
	}
	while (cmd->args[++token])
	{
		if (has_var(env, cmd->args[token]))
			continue;
		else if (!has_var(env, cmd->args[token]))
			printf("%s", cmd->args[token]);
		if (cmd->args[token + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return ;
}
