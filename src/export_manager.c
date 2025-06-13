/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:04:09 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/13 14:04:21 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	aux_export(t_export **export, char *var, char *value)
{
	t_export	*temp;

	if (!export || !var)
		return (0);
	temp = *export;
	while (temp)
	{
		if (!ft_strcmp(temp->var, var))
		{
			if (temp->value)
				free(temp->value);
			if (value)
				temp->value = ft_strdup(value);
			else
				temp->value = NULL;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	ft_setexport(t_export **export, char *var, char *value)
{
	t_export	*new;

	if (!export || !var)
		return ;
	if (!aux_export(export, var, value))
		return ;
	new = (t_export *)malloc(sizeof(t_export));
	if (!new)
		return (merror("ft_setexport:new"));
	new->var = ft_strdup(var);
	if (!new->var)
		return (merror("ft_setexport:new->var"));
	new->value = ft_strdup(value);
	new->next = *export;
	*export = new;
}

void	init_export(t_export **export, char **envp)
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
		if (matrix)
		{
			ft_setexport(export, matrix[0], matrix[1]);
			ft_clean_matrix(matrix);
		}
		i++;
	}
	return ;
}
