/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:33:31 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/06 17:55:51 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_str(char *s)
{
	char	*temp;
	t_bool	quotes[2];

	if (!s)
		return (NULL);
	init_proc((const char **)&temp, s, &quotes[0], &quotes[1]);
	while (*s)
	{
		check_char_quote((const char **)&s, &quotes[0], &quotes[1]);
		if (!quotes[0] && !quotes[1] && ((*s == '|') || (*s == '&')))
		{
			temp = s++;
			if (*temp == *s)
				return (new_word(temp, s));
		}
		if ((!quotes[0] && !quotes[1] && ((*s == '<') || (*s == '>'))))
		{
			temp = s + 2;
			if (*(s + 1) && *temp && *temp == *s && *s == *(s + 1))
				return (new_word(temp, temp + 1));
		}
		if (*s)
			s++;
	}
	return (NULL);
}

char	*syntax_error_check(char *input)
{
	char	*error;
	char	**matrix;
	int		i;

	error = NULL;
	matrix = ft_params(input);
	if (!matrix)
		return (NULL);
	i = -1;
	while (matrix[++i])
	{
		error = check_str(matrix[i]);
		if (error)
			return (ft_clean_matrix(matrix), error);
	}
	return (ft_clean_matrix(matrix), error);
}

/// @brief Function that send a error message of memory allocation to STDERR.
/// @param s Name of the function that malloc error has occured.
void	merror(char *s)
{
	if (s)
	{
		ft_putstr_fd("Malloc:", 2);
		ft_putendl_fd(s, 2);
	}
}

void	parser_error(char *error_msg, int fd)
{
	ft_putstr_fd(ERR_BAD_FORMAT, fd);
	if (error_msg)
		ft_putendl_fd(error_msg, fd);
	else
		ft_putstr_fd(TOKEN_NEWLINE, 2);
}
