/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_basics.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:26 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:37:39 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_char_allowed(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

int	check_file_extension(char *map_filepath, char *extension)
{
	int	len;
	int	ext_len;
	int	i;

	len = ft_strlen_lf(map_filepath, 0);
	ext_len = ft_strlen_lf(extension, 0);
	if (len <= ext_len)
		return (0);
	i = 0;
	while (i < ext_len)
	{
		if (map_filepath[len - ext_len + i] != extension[i])
			return (0);
		i++;
	}
	return (1);
}

int	validate_elements(t_mlx_data *env_p)
{
	int	i;
	int	j;
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	i = -1;
	while (++i < env_p->map_height)
	{
		j = -1;
		while (env_p->map[i][++j] != '\0')
		{
			if (env_p->map[i][j] == 'P')
				player_count++;
			else if (env_p->map[i][j] == 'E')
				exit_count++;
			else if (env_p->map[i][j] == 'C')
				collectible_count++;
		}
	}
	env_p->collectible_count = collectible_count;
	return (!(player_count != 1 || exit_count != 1 || collectible_count < 1));
}

int	validate_walls(t_mlx_data *env_p)
{
	int	i;
	int	j;

	i = 0;
	while (i < env_p->map_height)
	{
		if (env_p->map[i][0] != '1' ||
			env_p->map[i][env_p->map_width - 1] != '1')
			return (0);
		i++;
	}
	j = 0;
	while (j < env_p->map_width)
	{
		if (env_p->map[0][j] != '1' ||
			env_p->map[env_p->map_height - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	validate_map(t_mlx_data *env_p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env_p->map_height)
	{
		j = -1;
		while (env_p->map[i][++j] != '\0')
		{
			if (!is_char_allowed(env_p->map[i][j]))
				return (error_msg("char"), free_map(env_p), 0);
		}
		if (j != env_p->map_width)
			return (error_msg("rect"), free_map(env_p), 0);
	}
	if (!validate_elements(env_p))
		return (error_msg("elements"), free_map(env_p), 0);
	if (!validate_walls(env_p))
		return (error_msg("walls"), free_map(env_p), 0);
	return (1);
}
