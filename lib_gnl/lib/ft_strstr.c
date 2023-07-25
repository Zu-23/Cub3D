/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:46:03 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/25 18:46:08 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*p1;
	const char	*p2;
	const char	*p3;

	if (*needle == '\0')
		return ((char *)haystack);
	p1 = haystack;
	while (*p1 != '\0')
	{
		p2 = needle;
		p3 = p1;
		while (*p2 != '\0' && *p3 == *p2)
		{
			p2++;
			p3++;
		}
		if (*p2 == '\0')
			return ((char *)p1);
		p1++;
	}
	return (NULL);
}
