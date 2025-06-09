#include "minishell.h"

void	ft_setexport(t_export **export, char *var, char *value)
{
	t_export	*temp;
	
	temp = *export;
	while (temp)
	{
		if (!ft_strcmp(temp->var, var))
		{
			if (temp->value)
			{
				free(temp->value);
				temp->value = ft_strdup(value);
			}
			else
				temp->value = NULL;
			return ;
		}
		temp = temp->next;
	}
	t_export	*new = (t_export *)malloc(sizeof(t_export));
	new->var = ft_strdup(var);
	if (new->value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
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
		ft_setexport(export, matrix[0], matrix[1]);
		// printf("env_var: %s=%s\n", (*env)->var, (*env)->value); // printa a env toda basicamente
		ft_clean_matrix(matrix);
		i++;
	}
	return ;
}
