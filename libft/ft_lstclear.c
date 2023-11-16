/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:43:24 by jingchen          #+#    #+#             */
/*   Updated: 2022/10/25 21:10:57 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*backup;

	if (lst && del)
	{
		while ((*lst) != 0)
		{
			backup = (*lst)->next;
			ft_lstdelone((*lst), del);
			*lst = backup;
		}
	}
}
