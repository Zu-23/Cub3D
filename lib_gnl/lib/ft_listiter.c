/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:52:30 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/25 18:53:42 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_listiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	if (!*lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		f(*lst->content);
		ptr = (*lst)->next;
	}
}
