#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/include/libft.h"


typedef struct s_cmd
{
	int				argc; // quantidade de tokens
	char			**argv; // Comando + argumentos
	char			*infile; // Para redirecionamento <
	char			*outfile; // Para > ou >>
	int				append; // 0 para >, 1 para >>
	int				heredoc; // 1 se for <<, 0 caso contrário
	char			*delimiter; // Delimitador do heredoc
	struct s_cmd	*next; // Para pipes
}	t_cmd;


// misc
void	printascii(void);

// built in functions:
void	echo(t_cmd cmd);
void	pwd(t_cmd cmd);
void	cd(t_cmd cmd);
// void	update_pwd_env();