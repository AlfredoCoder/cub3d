/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:47:36 by alde-jes          #+#    #+#             */
/*   Updated: 2024/05/21 11:47:41 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str > 8 && *str < 14))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign *= -1;
		}
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
