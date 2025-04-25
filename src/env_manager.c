/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:17:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/25 12:26:25 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_env **env, char *var, char *value)
{
	t_env	*temp;
	
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
	t_env	*new = (t_env *)malloc(sizeof(t_env));
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
		// printf("env_var: %s=%s\n", (*env)->var, (*env)->value); // printa a env toda basicamente
		ft_clean_matrix(matrix);
		i++;
	}
	return ;
}
