/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:59:13 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/26 15:29:54 by pmoreira         ###   ########.fr       */
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
	while (start < end)
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

char	*new_word(const char *start, const char *end)
{
	char	*word;
	int		i;

	if (!start || !end)
		return (NULL);
	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i++] = *start;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	*get_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}
