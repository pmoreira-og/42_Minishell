#include "minishell.h"

static void	unset_export(t_export **export, t_cmd *cmd, t_hell *hell)
{
	t_export	*temp;
	t_export	*prev;

	temp = *export;
	prev = NULL;
	(void)hell;
	if (!cmd->args[1])
		return ;
	while (temp)
	{
		if (!ft_strcmp(temp->var, cmd->args[1]))
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

static void	unset_env(t_env **env, t_cmd *cmd, t_hell *hell)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	(void)hell;
	if (!cmd->args[1])
		return ;
	while (temp)
	{
		if (!ft_strcmp(temp->var, cmd->args[1]))
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
	unset_env(env, cmd, hell);
	unset_export(export, cmd, hell);
}
