/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:19:05 by pmoreira          #+#    #+#             */
/*   Updated: 2024/11/19 13:27:49 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include "libft.h"

int		ft_printf_fd(int fd, const char *input, ...);
int		putstr_fd(char *s, int fd);
int		ft_printnbr_fd(int num, int fd);
int		ft_itoh_fd(unsigned int nbr, char type, int fd);
int		ft_printunbr_fd(unsigned int num, int fd);
int		ft_printptr_fd(unsigned long ptr, int fd);

#endif