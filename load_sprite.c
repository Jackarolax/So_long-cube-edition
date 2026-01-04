/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:20 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:45:19 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Load sprite into env from XPM file
void	load_sprite(t_mlx_data *env_p, t_image *image_p, char *path)
{
	int	check_width;
	int	check_height;

	image_p->img = mlx_xpm_file_to_image(env_p->mlx, path, &check_width,
			&check_height);
	if (!image_p->img)
	{
		ft_printf("Error: Could not load sprite %s\n", path);
		destroy_everything_and_exit(env_p, 1);
		exit(1);
		return ;
	}
	if (check_width != image_p->width || check_height != image_p->height)
	{
		ft_printf("Error: Sprite %s has \
incorrect dimensions (expected %dx%d, got %dx%d)\n",
			path, image_p->width, image_p->height, check_width, check_height);
		destroy_everything_and_exit(env_p, 1);
		exit(1);
		return ;
	}
	image_p->addr = mlx_get_data_addr(image_p->img, &image_p->bpp,
			&image_p->line_length, &image_p->endian);
}
