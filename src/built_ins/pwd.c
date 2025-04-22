#include "minishell.h"
#include <readline/history.h>
#include <unistd.h>

void	pwd(t_cmd cmd)
{
	char *current;

	(void)cmd;
	current = getcwd(NULL, 0);
	if (!current)
		printf("Error 'pwd'\n");
	printf("%s\n", current);
	free(current);
	return ;
}
