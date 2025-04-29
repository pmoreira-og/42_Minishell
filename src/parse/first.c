/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:39:15 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/25 15:14:47 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_bool	is_command(char *s, t_token *tok, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	(void) tok;
	while(path && path[i])
	{
		temp = ft_strjoin(path[i], s);
		if (!temp)
			return (FALSE);
		if (access(temp, F_OK) != -1)
			return (TRUE);
		free(temp);
		i++;
	}
	return (FALSE);
}

void	token_type(char *s, char **path)
{
	printf("%s -> ", s);
	if (is_command(s, NULL, path))
		printf("TRUE\n");
	else
		printf("FALSE\n");
}

void	print_input(char *input, t_hell *data)
{
	char	**matrix;
	int	i;

	data->path = ft_getenv(data->envp, "PATH", ':');
	if (!data->path)
		return ((void) printf("Error path \n"));
	matrix = ft_parse(input, ' ');
	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
		token_type(matrix[i], data->path);
	ft_clean_matrix(matrix);
}
