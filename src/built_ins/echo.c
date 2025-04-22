#include "minishell.h"

// echo
// echo arg
// echo flag + arg
// echo redirects (ver depois)

void	echo(t_cmd cmd)
{
	int	token;
	int	flag;

	flag = 0;
	token = 0;
	if (cmd.argv[1] == NULL)
		return((void)printf("\n"));
	if (!ft_strcmp(cmd.argv[1], "-n"))
	{
		token++;
		flag++;
	}
	while (cmd.argv[++token])
	{
		printf("%s", cmd.argv[token]);
		if (cmd.argv[token + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return ;
}
