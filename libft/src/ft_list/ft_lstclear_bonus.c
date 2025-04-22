/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreira <pmoreira@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:10:18 by pmoreira          #+#    #+#             */
/*   Updated: 2025/02/04 14:20:19 by pmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst == 0)
		return ;
	else
	{
		temp = *lst;
		while ((*lst)->next != 0)
		{
			del((*lst)->content);
			temp = (*lst)->next;
			free((*lst));
			(*lst) = temp;
		}
		del((*lst)->content);
		free(*lst);
	}
	*lst = 0;
}
