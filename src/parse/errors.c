/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:33:31 by pmoreira          #+#    #+#             */
/*   Updated: 2025/05/30 12:06:39 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// syntax_error_check(input);

void	parser_error(char *error_msg, int fd)
{
	ft_putstr_fd(ERR_BAD_FORMAT, fd);
	if (error_msg)
		ft_putendl_fd(error_msg, fd);
	else
		ft_putstr_fd(TOKEN_NEWLINE, 2);
}
