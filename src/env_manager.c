/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:17:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/13 14:01:30 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_env **env, char *var, char *value)
{
	t_env	*temp;
	t_env	*new;

	temp = *env;
	while (temp)
	{
		if (!ft_strcmp(temp->var, var))
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	new = (t_env *)malloc(sizeof(t_env));
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

void	init_env(t_env **env, char **envp)
{
	char	**matrix;
	int		i;

	i = 0;
	while (envp[i])
	{
		matrix = ft_split_once(envp[i], '=');
		if (!matrix || !matrix[0] || !matrix[1])
		{
			ft_clean_matrix(matrix);
			i++;
			continue ;
		}
		ft_setenv(env, matrix[0], matrix[1]);
		ft_clean_matrix(matrix);
		i++;
	}
	return ;
}
