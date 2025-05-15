/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:58 by ernda-si          #+#    #+#             */
/*   Updated: 2025/05/15 10:55:48 by pmoreira         ###   ########.fr       */
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
	if (cmd->argv[1][i] == '-')
	{
		i++;
		while (cmd->argv[1][i] == 'n')
		{
			i++;
			if (!cmd->argv[1][i])
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
	if (cmd->argv[1] == NULL)
		return((void)printf("\n"));
	if (ft_check_n(cmd))
	{
		token++;
		flag++;
	}
	while (cmd->argv[++token])
	{
		if (has_var(env, cmd->argv[token]))
			continue;
		else if (!has_var(env, cmd->argv[token]))
			printf("%s", cmd->argv[token]);
		if (cmd->argv[token + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return ;
}
