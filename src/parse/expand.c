/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:54 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/06 19:09:09 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_name(char **start, char **s, char *end)
{
	if (*s < end && (isdigit(**s) || **s == '\?'))
		(*s)++;
	else if (*s < end && valid_expand(**s))
	{
		(*start)++;
		while (*s < end && valid_expand(**s))
			(*s)++;
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
	else
		*result = ft_expand(*result, (get_env(&hell->env, *new_str)), new_str);
}

char	*expand_vars(char *s, char *end, t_hell *hell)
{
	char	*result;
	char	*start;
	char	*temp;

	result = NULL;
	while (s < end)
	{
		start = s++;
		if (*start == '$' && *s && (valid_expand(*s) || *s == '\?'))
		{
			skip_name(&start, &s, end);
			temp = new_word(start, s);
			concat_expand(&result, &temp, hell);
		}
		else
		{
			while ((s < end) && *s && *s != '$')
				s++;
			temp = remove_quotes(start, s);
			result = ft_expand(result, temp, &temp);
		}
	}
	return (result);
}

char	*expand_heredoc(char *s, char *end, t_hell *hell)
{
	char	*result;
	char	*start;
	char	*temp;

	result = NULL;
	while (s < end)
	{
		start = s++;
		if (*start == '$' && *s && (valid_expand(*s) || *s == '\?'))
		{
			skip_name(&start, &s, end);
			temp = new_word(start, s);
			concat_expand(&result, &temp, hell);
		}
		else
		{
			while ((s < end) && *s && *s != '$')
				s++;
			temp = new_word(start, s);
			result = ft_expand(result, temp, &temp);
		}
	}
	return (result);
}
