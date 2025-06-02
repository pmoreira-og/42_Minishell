/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:55:22 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/02 10:23:18 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(int c)
{
	return (c == '\'' || c == '\"');
}

void	check_char_quote(const char **s, t_bool *quote, t_bool *d_quote)
{
	if (!s)
		return ;
	check_quotes(**s, quote, d_quote);
	if (**s == '\\' && *(*s + 1) && is_quotes(*(*s + 1)))
	{
		*quote = FALSE;
		*d_quote = FALSE;
		*s += 1;
	}
}

int	quotes_check(char *input)
{
	t_bool		quote;
	t_bool		d_quote;
	char		*error;
	const char	*temp;

	if (!input)
		return (0);
	init_proc(&temp, (const char *) input, &quote, &d_quote);
	while (*temp)
	{
		check_char_quote(&temp, &quote, &d_quote);
		temp++;
	}
	if (d_quote || quote)
		return (ft_putstr_fd(ERR_QUOTES, 2), 0);
	error = syntax_error_check(input);
	if (error)
		return (parser_error(error, 2), free(error), 0);
	// else
	// 	error = syntax_check2(input);
	// if (error)
	// 	return (parser_error(error, 2), free(error), 0);
	return (1);
}

void	check_quotes(int c, t_bool *quote, t_bool *d_quote)
{
	if (c == '\'' && *quote)
	{
		*quote = FALSE;
		return ;
	}
	else if (c == '\"' && *d_quote)
	{
		*d_quote = FALSE;
		return ;
	}
	if (c == '\'' && !(*d_quote))
	{
		*quote = TRUE;
		return ;
	}
	else if (c == '\"' && !(*quote))
	{
		*d_quote = TRUE;
		return ;
	}
}
