/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:54 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/22 13:21:33 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_expand_name(char **start, char **s, char *end)
{
	*start = *s;
	(*s)++;
	if (*s < end && is_quotes(**s))
		return ;
	if (*s < end && (isdigit(**s) || **s == '\?'))
	{
		(*s)++;
		return ;
	}
	if (*s < end && valid_expand(**s))
	{
		(*start)++;
		while (*s < end && valid_expand(**s))
			(*s)++;
		return ;
	}
}

void	concat_expand(char **result, char **new_str, t_hell *hell)
{
	char	*temp;

	if (!ft_strncmp(*new_str, "$\?", 2))
	{
		temp = ft_itoa(hell->status);
		if (!temp)
			return ;
		if (!(*result))
			*result = ft_strdup("");
		*result = ft_expand(*result, temp, new_str);
		free(temp);
	}
	else if (!ft_strncmp(*new_str, "$", 2))
		*result = ft_expand(*result, *new_str, new_str);
	else
		*result = ft_expand(*result, (get_env(&hell->env, *new_str)), new_str);
}

int	localized_expansions(char *start, char *end)
{
	if (!start || !end)
		return (0);
	return (*start == '$' && *(start + 1) == '\"' && *(end - 1) == '\"');
}

char	*localized_expander(char *start, char *end, t_hell *hell)
{
	char	*new_concat;
	char	*new_start;
	char	*new_end;

	new_start = start + 2;
	new_end = end - 1;
	new_concat = expand_vars(new_start, new_end, hell);
	if (!new_concat)
		return (NULL);
	return (new_concat);
}

char	*expand_vars(char *s, char *end, t_hell *hell)
{
	char	*start;
	char	*result;
	char	*temp;

	result = NULL;
	if (localized_expansions(s, end))
		return (localized_expander(s, end, hell));
	while (s < end)
	{
		if (*s == '$')
		{
			skip_expand_name(&start, &s, end);
			temp = new_word(start, s);
			concat_expand(&result, &temp, hell);
		}
		else
		{
			start = s;
			while ((s < end) && *s && *s != '$')
				s++;
			temp = new_word(start, s);
			result = ft_expand(result, temp, &temp);
		}
	}
	return (result);
}
