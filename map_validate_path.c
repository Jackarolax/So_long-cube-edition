/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:29 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:37:33 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//return value is if a ne field was visited
int	visited(char *grid_char_p,
				int *collectibles_found_p, int *exit_found_p)
{
	if (*grid_char_p == 'x' || *grid_char_p == '1')
		return (0);
	else if (*grid_char_p == '0')
	{
		*grid_char_p = 'x';
		return (1);
	}
	else if (*grid_char_p == 'C')
	{
		*grid_char_p = 'c';
		(*collectibles_found_p)++;
		return (1);
	}
	else if (*grid_char_p == 'E')
	{
		*grid_char_p = 'e';
		*exit_found_p = 1;
		return (1);
	}
	return (0);
}

int	visit_surrounding_fields(t_mlx_data *env_p, int *y_x,
				int *collectibles_found_p, int *exit_found_p)
{
	int	new_field_visited;
	int	grid_x;
	int	grid_y;

	grid_x = y_x[1];
	grid_y = y_x[0];
	new_field_visited = 0;
	new_field_visited += visited(&env_p->map[grid_y][grid_x + 1],
			collectibles_found_p, exit_found_p);
	new_field_visited += visited(&env_p->map[grid_y][grid_x - 1],
			collectibles_found_p, exit_found_p);
	new_field_visited += visited(&env_p->map[grid_y + 1][grid_x],
			collectibles_found_p, exit_found_p);
	new_field_visited += visited(&env_p->map[grid_y - 1][grid_x],
			collectibles_found_p, exit_found_p);
	return (new_field_visited);
}

int	is_visited_field(char field)
{
	return (field == 'x' || field == 'P' || field == 'c' || field == 'e');
}

int	validate_obtainability(t_mlx_data *env_p)
{
	static int	collectibles_found;
	static int	exit_found;
	int			i_j[2];
	int			new_field_visited;
	char		field;

	new_field_visited = 1;
	while (!(collectibles_found == env_p->collectible_count && exit_found)
		&& new_field_visited)
	{
		new_field_visited = 0;
		i_j[0] = -1;
		while (++i_j[0] < env_p->map_height)
		{
			i_j[1] = -1;
			while (env_p->map[i_j[0]][++i_j[1]] != '\0')
			{
				field = env_p->map[i_j[0]][i_j[1]];
				if (is_visited_field(field))
					new_field_visited += visit_surrounding_fields(env_p, i_j,
							&collectibles_found, &exit_found);
			}
		}
	}
	return (collectibles_found == env_p->collectible_count && exit_found);
}

void	renew_map(t_mlx_data *env_p)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env_p->map_height)
	{
		j = -1;
		while (env_p->map[i][++j] != '\0')
		{
			if (env_p->map[i][j] == 'x')
				env_p->map[i][j] = '0';
			else if (env_p->map[i][j] == 'c')
				env_p->map[i][j] = 'C';
			else if (env_p->map[i][j] == 'e')
				env_p->map[i][j] = 'E';
		}
	}
}
