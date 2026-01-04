/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:19:26 by anematol          #+#    #+#             */
/*   Updated: 2025/07/08 19:07:21 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_printf_i(int i)
{
	int	len;

	len = 1;
	if (i == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (i < 0)
	{
		ft_putchar('-');
		return (1 + ft_printf_i(-i));
	}
	else if (i >= 10)
	{
		len += ft_printf_i(i / 10);
		ft_putchar('0' + (i % 10));
	}
	else if (i < 10)
	{
		ft_putchar('0' + i);
	}
	return (len);
}
