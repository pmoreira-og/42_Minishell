/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:10:32 by ernda-si          #+#    #+#             */
/*   Updated: 2025/06/23 12:34:47 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_export(t_export **export, char *target)
{
	t_export	*temp;
	t_export	*prev;

	temp = *export;
	prev = NULL;
	if (!target)
		return ;
	while (temp)
	{
		if (!ft_strcmp(temp->var, target))
		{
			if (!prev)
				*export = temp->next;
			else
				prev->next = temp->next;
			free(temp->var);
			if (temp->value)
				free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

static void	unset_env(t_env **env, char *target)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	if (!target)
		return ;
	while (temp)
	{
		if (!ft_strcmp(temp->var, target))
		{
			if (!prev)
				*env = temp->next;
			else
				prev->next = temp->next;
			free(temp->var);
			if (temp->value)
				free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	mini_unset(t_env **env, t_cmd *cmd, t_export **export, t_hell *hell)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd->args[++i])
	{
		flag = 1;
		unset_env(env, cmd->args[i]);
		unset_export(export, cmd->args[i]);
	}
	if (flag)
		update_env(hell);
}
