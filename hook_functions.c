/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:19:14 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:03:59 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void *param)
{
	t_mlx_data	*env_p;

	env_p = (t_mlx_data *)param;
	destroy_everything_and_exit(env_p, 0);
	return (0);
}

int	handle_key_press(int keycode, void *param)
{
	t_mlx_data	*env_p;

	env_p = (t_mlx_data *)param;
	if (keycode == XK_Escape)
		close_window(param);
	if (keycode == XK_W || keycode == XK_w)
		env_p->up_pressed = 1;
	if (keycode == XK_S || keycode == XK_s)
		env_p->down_pressed = 1;
	if (keycode == XK_A || keycode == XK_a)
		env_p->left_pressed = 1;
	if (keycode == XK_D || keycode == XK_d)
		env_p->right_pressed = 1;
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	t_mlx_data	*env_p;

	env_p = (t_mlx_data *)param;
	if (keycode == XK_W || keycode == XK_w)
		env_p->up_pressed = 0;
	if (keycode == XK_S || keycode == XK_s)
		env_p->down_pressed = 0;
	if (keycode == XK_A || keycode == XK_a)
		env_p->left_pressed = 0;
	if (keycode == XK_D || keycode == XK_d)
		env_p->right_pressed = 0;
	return (0);
}

int	update_game(void *param)
{
	long int	time_diff;
	t_mlx_data	*env_p;

	env_p = (t_mlx_data *)param;
	gettimeofday(&env_p->t1, NULL);
	time_diff = (env_p->t1.tv_sec - env_p->t0.tv_sec)
		* 1000000 + env_p->t1.tv_usec - env_p->t0.tv_usec;
	if (time_diff < 16600)
		usleep(16600 - (time_diff));
	gettimeofday(&env_p->t0, NULL);
	move_player(env_p);
	draw_to_window(env_p);
	return (0);
}
