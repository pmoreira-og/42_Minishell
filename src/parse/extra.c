/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:59:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/15 11:46:19 by pmoreira         ###   ########.fr       */
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
