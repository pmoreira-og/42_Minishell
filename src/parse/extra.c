/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:59:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/14 14:12:13 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(int c, t_bool *quote, t_bool *d_quote)
{
	if (c == '\'' && *quote)
	{
		*quote = FALSE;
		return ;
	}
	else if (c == '"' && *d_quote)
	{
		*d_quote = FALSE;
		return ;
	}
	if (c == '\'' && !(*d_quote))
	{
		*quote = TRUE;
		return ;
	}
	else if (c == '"' && !(*quote))
	{
		*d_quote = TRUE;
		return ;
	}
}

void	init_proc(const char **start, const char *s, t_bool *quote, \
	t_bool *d_quote)
{
	*start = s;
	*quote = FALSE;
	*d_quote = FALSE;
}
