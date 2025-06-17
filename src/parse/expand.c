/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:54 by pmoreira          #+#    #+#             */
/*   Updated: 2025/06/17 10:44:33 by pmoreira         ###   ########.fr       */
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
			return (merror("concat_expand:itoa"));
		if (!(*result))
			*result = ft_strdup("");
		*result = ft_expand(*result, temp, new_str);
		if (!*result)
			return (free(temp), merror("concat_expand:expand"));
		free(temp);
	}
	else
		*result = ft_expand(*result, (get_env(&hell->env, *new_str)), new_str);
	if (!*result)
		return (merror("concat_expand:expand2"));
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

void	input_heredoc(int fd, char *limiter)
{
	char	*line;
	char	*temp;
	int		i;

	temp = NULL;
	i = get_hell(NULL)->lines;
	while (1)
	{
		temp = readline("> ");
		if (!temp || !ft_strcmp(temp, limiter))
			break;
		if (!ft_strcmp(temp, ""))
			line = ft_strdup("");
		else
			line = expand_heredoc(temp, &temp[ft_strlen(temp)], get_hell(NULL));
		if (!line)
			return (free(temp));
		ft_putendl_fd(line, fd);
		free(temp);
		temp = NULL;
		free(line);
		line = NULL;
	}
	if (!temp)
		ft_printf_fd(2, "%s%d%s'%s')\n", HEREDOC_EOF, i, HEREDOC_LIM, limiter);
}
