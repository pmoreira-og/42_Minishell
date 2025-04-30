#include "minishell.h"

void	mini_unset(t_env **env, t_cmd *cmd)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	if (!cmd->argv[1])
		return ;
	while (temp)
	{
		if (!ft_strcmp(temp->var, cmd->argv[1]))
		{
			if (!prev)
				*env = temp->next;
			else
				prev->next = temp->next;
			free(temp->var);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
