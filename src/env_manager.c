/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:17:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/17 12:10:12 by pmoreira         ###   ########.fr       */
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
	return (output);
	printf("%s\n", output);
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
		return(merror("update_env"), mini_cleaner(NULL, shell, 1));
	temp = shell->env;
	i = -1;
	while (temp && ++i)
	{
		shell->envp[i] = get_og_var(temp->var, temp->value);
		if (!shell->envp[i])
			return (mini_cleaner(NULL, shell, 1));
		temp = temp->next;
	}
	print_matrix(shell->envp);
}

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
