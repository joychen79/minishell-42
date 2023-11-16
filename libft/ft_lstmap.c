/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:40:46 by jingchen          #+#    #+#             */
/*   Updated: 2022/10/27 19:07:58 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstcopy;
	t_list	*aux;

	lstcopy = 0;
	if (lst && f && del)
	{
		while (lst)
		{
			aux = ft_lstnew(f(lst->content));
			if (!aux)
			{
				ft_lstclear(&aux, del);
				return (0);
			}
			ft_lstadd_back (&lstcopy, aux);
			lst = lst->next;
		}
	}
	return (lstcopy);
}
