/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:59:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/19 13:22:02 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_proc(const char **start, const char *s, t_bool *quote, \
	t_bool *d_quote)
{
	if (start && s)
		*start = s;
	*quote = FALSE;
	*d_quote = FALSE;
}

int	tab_counter(const char *start, const char *end)
{
	int		count;
	t_bool	quote;
	t_bool	d_quote;

	if (!start || !end)
		return (0);
	count = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while(start < end)
	{
		check_quotes(*start, &quote, &d_quote);
		if (*start == '\\' && !quote)
		{
			count++;
			start++;
		}
		if (*start)
			start++;
	}
	return (count);
}
