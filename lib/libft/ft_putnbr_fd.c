/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-jes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:54:24 by alde-jes          #+#    #+#             */
/*   Updated: 2024/10/07 20:54:26 by alde-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		i += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		i += ft_putnbr_fd(n / 10, fd);
		i += ft_putnbr_fd(n % 10, fd);
	}
	else
		i += ft_putchar_fd(n + '0', fd);
	return (i);
}
