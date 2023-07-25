/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:48:55 by alemsafi          #+#    #+#             */
/*   Updated: 2023/07/25 18:48:57 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*result;

	if (dest == NULL)
	{
		printf("Error: destination string is NULL");
		return (NULL);
	}
	result = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (result);
}
