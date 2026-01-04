/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:19:58 by anematol          #+#    #+#             */
/*   Updated: 2025/07/08 18:58:26 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(int h, int upper)
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

int	ft_printf_x(unsigned int h, int upper)
{
	int	len;

	len = 1;
	if (h >= 16)
	{
		len += ft_printf_x((h / 16), upper);
		ft_puthex((h % 16), upper);
	}
	else if (h < 16)
	{
		ft_puthex(h, upper);
	}
	return (len);
}
