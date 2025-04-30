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
		return(2);
	return(1);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char *tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

static char	*get_env_value(t_env **env, char *name)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

static char	*expand_vars(t_env **env, char *str)
{
	int		i; 
	int		start;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			temp = ft_substr(str, start, i - start);
			result = ft_strjoin_free(result, ft_strdup(get_env_value(env, temp)));
			free(temp);
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			temp = ft_substr(str, start, i - start);
			result = ft_strjoin_free(result, temp);
		}
	}
	return (result);
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
		else if (!has_var(env, cmd->argv[token]))
			printf("%s", cmd->argv[token]);
		if (cmd->argv[token + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return ;
}
