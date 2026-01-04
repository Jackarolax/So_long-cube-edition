/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:19:49 by anematol          #+#    #+#             */
/*   Updated: 2025/07/08 18:58:08 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_printf_u(unsigned int u)
{
	int	len;

	len = 1;
	if (u >= 10)
	{
		len += ft_printf_i(u / 10);
		ft_putchar('0' + (u % 10));
	}
	else if (u < 10)
	{
		ft_putchar('0' + u);
	}
	return (len);
}
