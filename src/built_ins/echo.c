/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:11:58 by ernda-si          #+#    #+#             */
/*   Updated: 2025/04/25 12:14:47 by pmoreira         ###   ########.fr       */
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
		return(0);
	return(1);
}

static char	*expand_vars(t_env **env, char *str)
{
	char	*str_temp;
	char	*env_var;
	t_env	*temp;
	int		i;

	i = -1;
	temp = *env;
	env_var = ft_strchr(str, '$');
	str_temp = ft_strdup("");
	while (temp && ft_strcmp(env_var + 1, temp->var))
		temp = temp->next;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			str_temp = ft_strjoin(str_temp, temp->value);
			//fazer uma funcao para encontrar o proximo $
			// como um strlen modificado para evitar alocacao de memoria excessiva.
			break;
		}
		str_temp[i] = str[i];
		// printf("str_temp: %s\n", str_temp);
	}
	return (str_temp);
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
			printf("%s", expand_vars(env, cmd->argv[token]));
		else
			printf("%s", cmd->argv[token]);
		if (cmd->argv[token + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return ;
}
