/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:17:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/07/04 11:32:00 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_og_var(char *var, char *value)
{
	char	*temp;
	char	*output;

	if (!var)
		return (NULL);
	temp = ft_strjoin(var, "=");
	if (!temp)
		return (merror("get_var:temp"), NULL);
	output = ft_strjoin(temp, value);
	if (!output)
		return (free(temp), merror("get_var:output"), NULL);
	return (free(temp), output);
}

void	update_env(t_hell *shell)
{
	t_env	*temp;
	int		i;

	temp = shell->env;
	i = 0;
	if (shell->envp)
	{
		ft_clean_matrix(shell->envp);
		shell->envp = NULL;
	}
	while (temp && ++i)
		temp = temp->next;
	shell->envp = ft_calloc(i + 1, sizeof(char *));
	if (!shell->envp)
		return (merror("update_env"), mini_cleaner(NULL, shell, 1));
	temp = shell->env;
	i = 0;
	while (temp)
	{
		shell->envp[i] = get_og_var(temp->var, temp->value);
		if (!shell->envp[i])
			return (merror("args"), mini_cleaner(NULL, shell, 1));
		temp = temp->next;
		i++;
	}
}

int	alloc_node(t_env **new, char *var, char *value)
{
	*new = (t_env *)malloc(sizeof(t_env));
	if (!*new)
		return (merror("ft_setenv:*new"), 0);
	(*new)->var = ft_strdup(var);
	if (!(*new)->var)
		return (merror("ft_setenv:(*new)->var"), free((*new)), 0);
	(*new)->value = ft_strdup(value);
	if (!(*new)->value)
	{
		merror("ft_setenv:(*new)->value");
		return (free((*new)->var), free((*new)), 0);
	}
	return (1);
}

void	ft_setenv(t_env **env, char *var, char *value)
{
	t_env	*temp;
	t_env	*new;

	if (!env)
		return ;
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
	if (!alloc_node(&new, var, value))
		return ;
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
