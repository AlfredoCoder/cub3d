/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:08:46 by alde-jes          #+#    #+#             */
/*   Updated: 2024/05/29 10:08:49 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[len] != '\0' && len < size - 1)
	{
		dest[len] = src[len];
		len++;
	}
	if (len < size)
		dest[len] = '\0';
	return (ft_strlen(src));
}
