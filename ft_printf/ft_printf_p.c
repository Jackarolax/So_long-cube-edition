/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:19:35 by anematol          #+#    #+#             */
/*   Updated: 2025/07/08 19:06:25 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex_p(int h, int upper)
{
	char	c;

	if (h < 10)
		c = '0' + h;
	else if (upper)
		c = 'A' + (h - 10);
	else
		c = 'a' + (h - 10);
	write(1, &c, 1);
}

static int	ft_printf_x_p(uintptr_t h, int upper)
{
	int	len;

	len = 1;
	if (h >= 16)
	{
		len += ft_printf_x_p((h / 16), upper);
		ft_puthex_p((h % 16), upper);
	}
	else if (h < 16)
	{
		ft_puthex_p(h, upper);
	}
	return (len);
}

int	ft_printf_p(uintptr_t p)
{
	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	return (2 + ft_printf_x_p(p, 0));
}
