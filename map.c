/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:53 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:49:57 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_sprite_dimensions(t_mlx_data *env_p)
{
	int	size;
	int	size_small;

	env_p->block_size = 50;
	env_p->height = env_p->map_height * env_p->block_size;
	env_p->width = env_p->map_width * env_p->block_size;
	size = env_p->block_size;
	size_small = size / 2;
	env_p->player_img.width = size_small;
	env_p->player_img.height = size_small;
	env_p->wall_img.width = size;
	env_p->wall_img.height = size;
	env_p->collectible_img.width = size_small;
	env_p->collectible_img.height = size_small;
	env_p->exit_open_img.width = size;
	env_p->exit_open_img.height = size;
	env_p->exit_closed_img.width = size;
	env_p->exit_closed_img.height = size;
}

void	set_player_start_position(t_mlx_data *env_p)
{
	int		grid_x;
	int		grid_y;
	char	**map;
	int		center_width;
	int		center_height;

	center_width = (env_p->block_size - env_p->player_img.width) / 2;
	center_height = (env_p->block_size - env_p->player_img.height) / 2;
	map = env_p->map;
	grid_y = 0;
	while (grid_y < env_p->map_height)
	{
		grid_x = 0;
		while (grid_x < env_p->map_width)
		{
			if (map[grid_y][grid_x] == 'P')
			{
				env_p->player_x = grid_x * env_p->block_size + center_width;
				env_p->player_y = grid_y * env_p->block_size + center_height;
				return ;
			}
			grid_x++;
		}
		grid_y++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	i = 0;
	while (ptr_s1[i] != '\0' && ptr_s2[i] != '\0')
	{
		if (ptr_s1[i] != ptr_s2[i])
			return (ptr_s1[i] - ptr_s2[i]);
		i++;
	}
	return (0);
}

int	format_map(t_mlx_data *env_p)
{
	int	i;
	int	len;

	i = 0;
	while (i < env_p->map_height)
	{
		len = ft_strlen_lf(env_p->map[i], 1);
		env_p->map[i][len - 1] = '\0';
		i++;
	}
	return (0);
}

int	load_map(t_mlx_data *env_p, char *map_filepath)
{
	if (!check_file_extension(map_filepath, ".ber"))
		return (error_msg("extension"), 1);
	if (get_map(env_p, map_filepath) != 0)
		return (1);
	format_map(env_p);
	if (!validate_map(env_p))
		return (1);
	set_sprite_dimensions(env_p);
	set_player_start_position(env_p);
	if (!validate_obtainability(env_p))
		return (error_msg("obtainable"), free_map(env_p), 1);
	renew_map(env_p);
	return (0);
}
