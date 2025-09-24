/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:28:55 by alde-jes          #+#    #+#             */
/*   Updated: 2024/05/18 15:28:57 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t size)
{
	unsigned char	*p;

	p = (unsigned char *) ptr;
	while (size--)
	{
		if (*p == (unsigned char)value)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
