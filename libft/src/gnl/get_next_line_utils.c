/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:22:15 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/07 11:30:27 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len(const char *str)
{
	size_t	i;

	if (str == 0)
		return (0);
	i = 0;
	while (str[i] != 0 && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_fill_line(char *buffer, int fd)
{
	int		rd;
	char	*temp;

	rd = 1;
	temp = 0;
	while (ft_str_nl(temp) == NULL && rd > 0)
	{
		if (*buffer == 0)
			rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
			break ;
		temp = ft_strjoin_nl(temp, buffer);
		if (temp == 0)
			return (0);
		ft_refill_buffer(buffer);
	}
	if (ft_str_nl(temp) == NULL && rd < 0)
		return (free(temp), NULL);
	return (temp);
}

char	*ft_strjoin_nl(char *line, char *buffer)
{
	char	*join;
	ssize_t	i;

	if (line == NULL)
	{
		line = (char *) malloc(1);
		line[0] = 0;
	}
	join = (char *) malloc((ft_len(line) +ft_len(buffer) + 1) * sizeof(char));
	if (join == 0)
		return (0);
	i = -1;
	while (line[++i])
		join[i] = line[i];
	while (*buffer && *buffer != '\n')
	{
		join[i++] = *buffer;
		buffer++;
	}
	if (*buffer == '\n')
		join[i++] = '\n';
	join[i] = 0;
	free(line);
	return (join);
}

void	ft_refill_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_len(buffer);
	while (buffer[j] != 0)
		buffer[i++] = buffer[j++];
	while (i < BUFFER_SIZE)
		buffer[i++] = 0;
}

char	*ft_str_nl(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (&str[i]);
		i++;
	}
	return (0);
}
