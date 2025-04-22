#include "minishell.h"

void	cd(t_cmd cmd)
{
	char	*path;

	(void)cmd;
	path = NULL;
	printf("path: %s\n", path);
	if (ft_strcmp(cmd.argv[1], "."))
		return ;
	// else if (ft_strcmp(cmd.argv[1], ".."))
	// {

	// }
	else if (cmd.argv[1] == NULL)
	{
		path = getenv("HOME");
		chdir(path);
	}
	// else
	// {

	// }
	// chdir();
}
