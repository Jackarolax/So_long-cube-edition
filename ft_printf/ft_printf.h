/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:51:56 by anematol          #+#    #+#             */
/*   Updated: 2025/07/09 13:22:29 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf_c(char c);
int	ft_printf_s(char *s);
int	ft_printf_i(int i);
int	ft_printf_u(unsigned int u);
int	ft_printf_p(uintptr_t p);
int	ft_printf_x(unsigned int h, int upper);
int	ft_printf(const char *s, ...);

#endif
