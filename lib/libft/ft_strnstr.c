/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:11:48 by alde-jes          #+#    #+#             */
/*   Updated: 2024/05/29 10:11:57 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *bus, const char *str, size_t size)
{
	size_t	len;

	len = ft_strlen(str);
	if (len == 0)
		return ((char *)bus);
	while (*bus && size >= len)
	{
		if (ft_strncmp(bus, str, len) == 0)
			return ((char *)bus);
		bus++;
		size--;
	}
	return (NULL);
}
