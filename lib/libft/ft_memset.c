/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:45:45 by alde-jes          #+#    #+#             */
/*   Updated: 2024/05/15 11:45:47 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t num)
{
	unsigned char	*pt;

	pt = (unsigned char *)ptr;
	while (num > 0)
	{
		pt[num - 1] = val;
		num--;
	}
	return (pt);
}
