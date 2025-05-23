/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:21:45 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/23 16:30:04 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_expand_zones(char *input)
{
	int		count;
	t_bool	quote;
	t_bool	d_quote;
	
	count = 0;
	init_proc(NULL, NULL, &quote, &d_quote);
	while (*input)
	{
		check_char_quote((const char **)&input, &quote, &d_quote);
		if (!quote && !d_quote && *input == '$' && is_quotes(*(input + 1)))
			count++;
		input++;
	}
	return (count);
}