#include "minishell.h"
	
int	is_builtin(t_cmd cmd)
{
	if (!ft_strcmp(cmd.argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd.argv[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd.argv[0], "cd"))
		return (1);
	return (0);
}

void	list_builtin(t_cmd cmd)
{
	if (!ft_strcmp(cmd.argv[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd.argv[0], "pwd"))
		pwd(cmd);
	else if (!ft_strcmp(cmd.argv[0], "cd"))
		cd(cmd);
}

int	main(int ac, char **av)
{
	char	*input;
	t_cmd	cmd;

	(void)ac;
	(void)av;
	input = "";
	cmd.argv = NULL;
	cmd.argc = ac;
	if (ac == 2 && !ft_strcmp(av[1], "-b"))
		printASCII();
	while (strcmp(input, "exit"))
	{
		input = readline("Minishell$ ");
		cmd.argv = ft_split(input, ' ');
		if (is_builtin(cmd) && cmd.argv[0])
			list_builtin(cmd);
	}
	free(input);
	return (0);
}
