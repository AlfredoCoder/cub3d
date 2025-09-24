/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:04:36 by alde-jes          #+#    #+#             */
/*   Updated: 2024/05/17 09:04:39 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest <= src || dest >= (src + n))
	{
		d = (unsigned char *)dest;
		s = (const unsigned char *)src;
		while (n--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		d = (unsigned char *)dest + n - 1;
		s = (const unsigned char *)src + n - 1;
		while (n--)
		{
			*d-- = *s--;
		}
	}
	return (dest);
}
