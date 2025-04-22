/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:06:28 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 16:04:13 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list *) malloc(sizeof(t_list));
	if (lst == 0)
		return (0);
	lst->content = content;
	lst->next = 0;
	return (lst);
}
