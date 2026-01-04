/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:21:12 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:29:53 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_collectible_at_player(t_mlx_data *env_p, int new_x, int new_y)
{
	int		grid_x;
	int		grid_y;
	char	**map;

	map = env_p->map;
	grid_x = (new_x + env_p->player_img.width / 2) / env_p->block_size;
	grid_y = (new_y + env_p->player_img.height / 2) / env_p->block_size;
	if (map[grid_y][grid_x] == 'C')
	{
		map[grid_y][grid_x] = '0';
		env_p->collectible_count--;
		ft_printf("Collectible at (%d, %d) collected!\n", grid_x, grid_y);
		if (env_p->collectible_count == 0)
			ft_printf("All collectibles collected! Exit is now open.\n");
	}
}

void	check_exit_at_player(t_mlx_data *env_p)
{
	int		top;
	int		bottom;
	int		right;
	int		left;
	char	**map;

	if (env_p->collectible_count > 0)
		return ;
	map = env_p->map;
	left = env_p->player_x / env_p->block_size;
	right = (env_p->player_x + env_p->player_img.width - 1) / env_p->block_size;
	top = env_p->player_y / env_p->block_size;
	bottom = (env_p->player_y + env_p->player_img.height - 1)
		/ env_p->block_size;
	if (map[top][left] == 'E'
		&& map[top][right] == 'E'
		&& map[bottom][left] == 'E'
		&& map[bottom][right] == 'E')
	{
		ft_printf("Exit at (%d, %d) reached! You win!\n", top, left);
		destroy_everything_and_exit(env_p, 0);
	}
}

void	check_element_collisions(t_mlx_data *env_p, int new_x, int new_y)
{
	check_collectible_at_player(env_p, new_x, new_y);
	check_exit_at_player(env_p);
}
