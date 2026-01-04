/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:06 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:04:01 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptrsrc;
	unsigned char	*ptrdest;

	if (src == NULL && dest == NULL)
		return (NULL);
	i = 0;
	ptrsrc = (unsigned char *)src;
	ptrdest = (unsigned char *)dest;
	while (i < n)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	return (ptrdest);
}

void	copy_background_to_buffer(t_mlx_data *env_p)
{
	ft_memcpy(env_p->buffer_img.addr, env_p->background_img.addr,
		env_p->background_img.height * env_p->background_img.line_length);
}

int	create_background(void *param)
{
	t_mlx_data	env;
	t_image		bg;
	float		factx;
	float		facty;
	int			i;

	env = *(t_mlx_data *)param;
	bg = ((t_mlx_data *)param)->background_img;
	factx = (float)env.width / 255.0f;
	facty = (float)env.height / 255.0f;
	i = 0;
	while (i < env.width * env.height)
	{
		put_pixel_to_image(bg,
			i % env.width, i / env.width,
			(255 - (int)(((float)(i / env.width) / facty))) * 1 * 256 * 256
			+ (255 - (int)((float)(i % env.width) / factx)) * 0 * 256
			+ 1 * (255 - (int)((float)(i / env.width) / facty) / 2
				- (int)((float)(i % env.width) / factx / 2)));
		i++;
	}
	draw_obstacles(&env);
	return (0);
}

int	draw_to_window(void *param)
{
	t_mlx_data	env;

	env = *(t_mlx_data *)param;
	copy_background_to_buffer(&env);
	draw_collectibles(&env);
	draw_exit(&env, env.collectible_count == 0);
	put_img_inside_img(env.player_img, env.buffer_img,
		env.player_x, env.player_y);
	mlx_put_image_to_window(env.mlx, env.win, env.buffer_img.img, 0, 0);
	return (0);
}
