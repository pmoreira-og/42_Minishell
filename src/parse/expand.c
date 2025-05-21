/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:54 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/21 16:43:46 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/// @brief Join the 2 strings, free the s1 and free the s2 if the pointer are 
///		given.
/// @param s1 Output string.
/// @param s2 Temp string.
/// @param temp Address of Temp.
/// @return Strjoin.
char	*ft_expand(char *s1, char *s2, char **temp)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (temp)
		free(*temp);
	return (tmp);
}

char	*expand_vars(char *s, char *end, t_hell *hell)
{
	char	*start;
	char	*result;
	char	*temp;

	result = NULL;
	while (s < end)
	{
		if (*s == '$' && *(s + 1) && valid_expand(*(s + 1)))
		{
			start = ++s;
			skip_expand_name(&s, end);
			temp = new_word(start, s);
			concat_expand(&result, &temp, hell, &s);
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
