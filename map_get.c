/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:23 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:03:55 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_msg(char *msg)
{
	if (ft_strcmp(msg, "extension") == 0)
		ft_printf("Map has to be in .ber format\n");
	else if (ft_strcmp(msg, "file") == 0)
		ft_printf("Error: Could not open map file\n");
	else if (ft_strcmp(msg, "empty") == 0)
		ft_printf("Error: Map is empty\n");
	else if (ft_strcmp(msg, "char") == 0)
		ft_printf("Error: Map contains invalid characters\n");
	else if (ft_strcmp(msg, "rect") == 0)
		ft_printf("Error: Map is not rectangular\n");
	else if (ft_strcmp(msg, "walls") == 0)
		ft_printf("Error: Map is not enclosed by walls\n");
	else if (ft_strcmp(msg, "elements") == 0)
		ft_printf("Error: Map must contain at exactly one player,\
 one exit, and at least one collectible\n");
	else if (ft_strcmp(msg, "memory") == 0)
		ft_printf("Error: Memory allocation failed\n");
	else if (ft_strcmp(msg, "obtainable") == 0)
		ft_printf("Error: No valid path to all collectibles and exit\n");
}

void	free_map(t_mlx_data *env_p)
{
	int	i;

	i = 0;
	while (i < env_p->map_height)
	{
		free(env_p->map[i]);
		i++;
	}
	free(env_p->map);
}

//returns map with one malloced line and frees the input
char	**map_add_line(char **map, int rows)
{
	char	**dup;
	int		i;

	dup = malloc((1 + rows) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		dup[i] = map[i];
		i++;
	}
	free(map);
	return (dup);
}

int	get_map(t_mlx_data *env_p, char *map_filepath)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
		return (error_msg("file"), 1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), error_msg("empty"), 1);
	env_p->map = malloc(sizeof(char *));
	if (!env_p->map)
		return (close(fd), free(line), error_msg("memory"), 1);
	env_p->map_width = ft_strlen_lf(line, 1) - 1;
	i = -1;
	while (++i >= 0 && line)
	{
		env_p->map = map_add_line(env_p->map, i);
		if (! env_p->map)
			return (close(fd), free(line), error_msg("memory"), 1);
		env_p->map[i] = line;
		line = get_next_line(fd);
	}
	return (env_p->map_height = i, close(fd), 0);
}
