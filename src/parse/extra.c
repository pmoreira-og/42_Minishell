/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:59:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/21 16:43:07 by pmoreira         ###   ########.fr       */
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

int	valid_expand(int c)
{
	return (ft_isalnum(c) || c == '_');
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

void	skip_expand_name(char **s, char *end)
{
	if((**s) && (isdigit(**s) || **s == '\?'))
	{
		*s += 1;
		return ;
	}
	while ((*s < end) && **s && valid_expand(**s))
		*s += 1;
}

void	concat_expand(char **result, char **new_str, t_hell *hell, char **ptr)
{
	char	*temp;

	(void) ptr;
	if (!ft_strcmp(*new_str, "\?"))
	{
		temp = ft_itoa(hell->status);
		if (!temp)
			return ;
		if (!(*result))
			*result = ft_strdup("");
		*result = ft_expand(*result, temp, new_str);
		free(temp);
	}
	else
			*result = ft_expand(*result, (get_env(&hell->env, *new_str)), new_str);
	
}
