/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:09 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 16:59:25 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//the ostacle sprite has to be initialized already
void	draw_obstacles(t_mlx_data *env_p)
{
	int		grid_x;
	int		grid_y;
	char	**map;

	map = env_p->map;
	if (!map)
	{
		ft_printf("Error: draw_obstacles called with NULL map\n");
		return ;
	}
	grid_y = 0;
	while (grid_y < env_p->map_height)
	{
		grid_x = 0;
		while (grid_x < env_p->map_width)
		{
			if (map[grid_y][grid_x] == '1')
				put_img_inside_img(env_p->wall_img,
					env_p->background_img,
					grid_x * env_p->block_size,
					grid_y * env_p->block_size);
			grid_x++;
		}
		grid_y++;
	}
}

void	draw_exit(t_mlx_data *env_p, int open)
{
	int		grid_x;
	int		grid_y;
	t_image	exit_img;

	if (open)
		exit_img = env_p->exit_open_img;
	else
		exit_img = env_p->exit_closed_img;
	grid_y = -1;
	while (++grid_y < env_p->map_height)
	{
		grid_x = -1;
		while (++grid_x < env_p->map_width)
		{
			if (env_p->map[grid_y][grid_x] == 'E')
				put_img_inside_img(exit_img,
					env_p->buffer_img,
					grid_x * env_p->block_size,
					grid_y * env_p->block_size);
		}
	}
}

void	draw_collectibles(t_mlx_data *env_p)
{
	int	grid_x;
	int	grid_y;
	int	padding;

	padding = (env_p->block_size - env_p->collectible_img.width) / 2;
	grid_y = 0;
	while (grid_y < env_p->map_height)
	{
		grid_x = 0;
		while (grid_x < env_p->map_width)
		{
			if (env_p->map[grid_y][grid_x] == 'C')
				put_img_inside_img(env_p->collectible_img,
					env_p->buffer_img,
					grid_x * env_p->block_size + padding,
					grid_y * env_p->block_size + padding);
			grid_x++;
		}
		grid_y++;
	}
}

void	delete_collectible_at_player(t_mlx_data *env_p)
{
	int		grid_x;
	int		grid_y;
	char	**map;

	map = env_p->map;
	if (!map)
	{
		ft_printf("Error: delete_collectible_at_player called with NULL \
map\n");
		return ;
	}
	grid_x = env_p->player_x / env_p->block_size;
	grid_y = env_p->player_y / env_p->block_size;
	if (map[grid_y][grid_x] == 'C')
	{
		map[grid_y][grid_x] = '0';
		ft_printf("Collectible at (%d, %d) collected!\n", grid_x, grid_y);
	}
}
