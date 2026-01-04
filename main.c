/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:20:08 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:03:56 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_env(t_mlx_data *env_p)
{
	env_p->mlx = NULL;
	env_p->win = NULL;
	env_p->up_pressed = 0;
	env_p->down_pressed = 0;
	env_p->left_pressed = 0;
	env_p->right_pressed = 0;
	env_p->up_counter = 0;
	env_p->down_counter = 0;
	env_p->left_counter = 0;
	env_p->right_counter = 0;
	env_p->buffer_img.img = NULL;
	env_p->buffer_img.width = env_p->width;
	env_p->buffer_img.height = env_p->height;
	env_p->background_img.img = NULL;
	env_p->background_img.width = env_p->width;
	env_p->background_img.height = env_p->height;
	env_p->player_img.img = NULL;
	env_p->wall_img.img = NULL;
	env_p->collectible_img.img = NULL;
	env_p->exit_open_img.img = NULL;
	env_p->exit_closed_img.img = NULL;
}

//can only be used after calling init_env()
void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code)
{
	if (env_p->buffer_img.img)
		mlx_destroy_image(env_p->mlx, env_p->buffer_img.img);
	if (env_p->background_img.img)
		mlx_destroy_image(env_p->mlx, env_p->background_img.img);
	if (env_p->player_img.img)
		mlx_destroy_image(env_p->mlx, env_p->player_img.img);
	if (env_p->wall_img.img)
		mlx_destroy_image(env_p->mlx, env_p->wall_img.img);
	if (env_p->collectible_img.img)
		mlx_destroy_image(env_p->mlx, env_p->collectible_img.img);
	if (env_p->exit_open_img.img)
		mlx_destroy_image(env_p->mlx, env_p->exit_open_img.img);
	if (env_p->exit_closed_img.img)
		mlx_destroy_image(env_p->mlx, env_p->exit_closed_img.img);
	if (env_p->win)
		mlx_destroy_window(env_p->mlx, env_p->win);
	if (env_p->mlx)
		mlx_destroy_display(env_p->mlx);
	free(env_p->mlx);
	free_map(env_p);
	exit(exit_code);
}

void	load_sprites(t_mlx_data *env_p)
{
	if (env_p->block_size == 50)
	{
		load_sprite(env_p, &env_p->player_img,
			"./sprites/player_25x25.xpm");
		load_sprite(env_p, &env_p->wall_img,
			"./sprites/wall_50x50.xpm");
		load_sprite(env_p, &env_p->collectible_img,
			"./sprites/collectible_25x25.xpm");
		load_sprite(env_p, &env_p->exit_closed_img,
			"./sprites/exit_closed_50x50.xpm");
		load_sprite(env_p, &env_p->exit_open_img,
			"./sprites/exit_open_50x50.xpm");
	}
	else
	{
		ft_printf("Error: Unsupported \
block size %d for sprites\n", env_p->block_size);
		destroy_everything_and_exit(env_p, 1);
	}
}

void	create_images(t_mlx_data *env_p)
{
	env_p->buffer_img.img = mlx_new_image(
			env_p->mlx,
			env_p->buffer_img.width,
			env_p->buffer_img.height);
	env_p->background_img.img = mlx_new_image(
			env_p->mlx,
			env_p->background_img.width,
			env_p->background_img.height);
	load_sprites(env_p);
	if (env_p->buffer_img.img == NULL || env_p->background_img.img == NULL)
		destroy_everything_and_exit(env_p, 1);
	env_p->buffer_img.addr = mlx_get_data_addr(
			env_p->buffer_img.img,
			&env_p->buffer_img.bpp,
			&env_p->buffer_img.line_length,
			&env_p->buffer_img.endian);
	env_p->background_img.addr = mlx_get_data_addr(
			env_p->background_img.img,
			&env_p->background_img.bpp,
			&env_p->background_img.line_length,
			&env_p->background_img.endian);
	create_background(env_p);
}

int	main(int argc, char **argv)
{
	t_mlx_data	env;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file>.ber\n", argv[0]);
		return (1);
	}
	if (load_map(&env, argv[1]) != 0)
		return (1);
	init_env(&env);
	env.mlx = mlx_init();
	if (env.mlx == NULL)
		return (destroy_everything_and_exit(&env, 1), 1);
	env.win = mlx_new_window(env.mlx, env.width, env.height, "So_Long");
	if (env.win == NULL)
		return (destroy_everything_and_exit(&env, 1), 1);
	create_images(&env);
	gettimeofday(&env.t0, NULL);
	mlx_hook(env.win, DestroyNotify, KeyPressMask, close_window, &env);
	mlx_hook(env.win, KeyPress, KeyPressMask, handle_key_press, &env);
	mlx_hook(env.win, KeyRelease, KeyReleaseMask, handle_key_release, &env);
	mlx_loop_hook(env.mlx, update_game, &env);
	mlx_loop(env.mlx);
}
