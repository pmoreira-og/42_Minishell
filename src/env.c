#include "minishell.h"

void	ft_setenv(t_env **env, char *var, char *value)
{
	t_env	*temp;
	
	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->var, var) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	t_env	*new = (t_env *)malloc(sizeof(t_env));
	new->var = ft_strdup(var);
	new->var = ft_strdup(value);
	new->next = *env;
	*env = new;
}
