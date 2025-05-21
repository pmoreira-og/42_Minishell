#include "minishell.h"

static int	identifier_check(char **matrix)
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

void	mini_export(t_env **env, t_cmd *cmd)
{
	char	**matrix;

	if (cmd->argc == 1)
		return ;
	matrix = ft_split_once(cmd->args[1], '=');
	if (!identifier_check(matrix))
	{
		printf("\033[1;31mMinishell\033[0m: export: %s: not a valid identifier\n", cmd->args[1]);
		return ;
	}
	else if (matrix[0] && matrix[1])
		ft_setenv(env, matrix[0], matrix[1]);
	else if (matrix[0] && !matrix[1])
		ft_setenv(env, matrix[0], "");
	printf("matrix[0]: %s\nmatrix[1]: %s\n", matrix[0], matrix[1]);
	return ;
}
