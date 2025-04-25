/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:39:15 by pmoreira          #+#    #+#             */
/*   Updated: 2025/04/24 15:15:08 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	print_input(char *input)
{
	char	**matrix;
	int	i;

	matrix = ft_parse(input, ' ');
	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
		printf("%s\n", matrix[i]);
	ft_clean_matrix(matrix);
}