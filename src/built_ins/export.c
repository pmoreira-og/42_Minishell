#include "minishell.h"

static int	
identifier_check(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[0][i])
	{
		if (matrix[0][i] == ' ' || matrix[0][i] == '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_export *export)
{
	t_export *temp;

	temp = export;
	while (temp)
	{
		if (!temp->value)
			printf("declare -x %s\n", temp->var);
		else
		{
			printf("declare -x %s=", temp->var);
			printf("%s\n", temp->value);
		}
		temp = temp->next;
	}
	return ;
}

void    mini_export(t_env **env, t_export **export, t_cmd *cmd)
{
	int i = 1;
	if (cmd->argc == 1)
		return (print_export(*export));
	while (i < cmd->argc)
	{
		char **matrix = ft_split_once(cmd->args[i], '=');
		if (!identifier_check(matrix))
			fprintf(stderr,
				"Minishell: export: `%s': not a valid identifier\n",
				cmd->args[i]);
		else if (matrix[0] && matrix[1])
		{
			ft_setenv(env, matrix[0], matrix[1]);
			ft_setexport(export, matrix[0], matrix[1]);
		}
		else if (matrix[0] && !matrix[1])
		{
			ft_setenv(env, matrix[0], "");
			ft_setexport(export, matrix[0], ""); // ver isso amanha + casos especificos
		}
		ft_clean_matrix(matrix);
		i++;
	}
}
