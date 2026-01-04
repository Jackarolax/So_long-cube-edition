/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:17 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:03:58 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Get pixel color from sprite
int	get_img_pixel(t_image image, int x, int y)
{
	char	*pixel;

	pixel = image.addr + (y * image.line_length + x * (image.bpp / 8));
	return (*(int *)pixel);
}

void	put_pixel_to_image(t_image image, int x, int y, int color)
{
	char	*dst;

	dst = image.addr + (y * image.line_length + x * (image.bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_img_inside_img(t_image small_image, t_image large_image,
						int x, int y)
{
	int	i;
	int	j;
	int	pixel_color;

	i = 0;
	while (i < small_image.height)
	{
		j = 0;
		while (j < small_image.width)
		{
			pixel_color = get_img_pixel(small_image, j, i);
			if ((pixel_color > 0)
				&& (x + j >= 0 && x + j < large_image.width)
				&& (y + i >= 0 && y + i < large_image.height))
			{
				put_pixel_to_image(large_image, x + j, y + i, pixel_color);
			}
			j++;
		}
		i++;
	}
}
