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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int		ft_printf(const char *input, ...);
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_printnbr(int n);
int		ft_itoh(unsigned int nbr, char type);
int		ft_printunbr(unsigned int num);
int		ft_printptr(unsigned long ptr);

#endif