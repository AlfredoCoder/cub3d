/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:08:34 by alde-jes          #+#    #+#             */
/*   Updated: 2024/05/29 10:08:37 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (dest[len] && len < size)
		len++;
	while (src[i] && (len + i + 1) < size)
	{
		dest[len + i] = src[i];
		i++;
	}
	if (len < size)
		dest[len + i] = '\0';
	return (len + ft_strlen(src));
}
