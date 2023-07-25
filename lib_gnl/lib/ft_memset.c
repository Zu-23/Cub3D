/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:49:35 by zhaddoum          #+#    #+#             */
/*   Updated: 2023/07/25 18:47:43 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int	i;
	unsigned char	val;

	val = (unsigned char)c;
	if (n == 0)
		return (str);
	i = 0;
	while (i < n)
	{
		*((char *)str + i) = val;
		i++;
	}
	return (str);
}
