/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ernda-si <ernda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:33:31 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/13 14:11:39 by ernda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handle <<< >>> || && as syntax errors.
/// @param s String to check.
/// @return Malloc with the char that caused the error.
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
		ft_printf_fd(2, "Malloc:%s\n", s);
}

void	parser_error(char *error_msg, int fd)
{
	if (error_msg)
		ft_printf_fd(fd, "%s%s\n", ERR_BAD_FORMAT, error_msg);
}

/// @brief Heredoc message for finishing with eof.
/// @param c Char code of the number of the line that eof occurs.
/// @param fd Fd where message gonna be written.
void	heredoc_eof(int c, int fd)
{
	if (fd > 0 && c)
		ft_printf_fd(fd, "%s%c%s\n", HEREDOC_EOF, c,
			" delimited by end-of-file");
}
