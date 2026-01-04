/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:18:54 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:06:34 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_moves(t_mlx_data *env_p, int new_x, int new_y)
{
	int	moved;

	moved = 0;
	if (new_y < env_p->player_y && ++moved)
		env_p->up_counter++;
	else if (new_y > env_p->player_y && ++moved)
		env_p->down_counter++;
	if (new_x < env_p->player_x && ++moved)
		env_p->left_counter++;
	else if (new_x > env_p->player_x && ++moved)
		env_p->right_counter++;
	if (moved)
		ft_printf("Up: %d Down: %d Left: %d Right: %d Total: %d\n",
			env_p->up_counter, env_p->down_counter,
			env_p->left_counter, env_p->right_counter,
			env_p->up_counter + env_p->down_counter
			+ env_p->left_counter + env_p->right_counter);
}

void	move_player_with_collisions(t_mlx_data *env_p, int new_x, int new_y)
{
	if (!check_collision(env_p, new_x, env_p->player_y))
	{
		count_moves(env_p, new_x, collision_position_y(env_p, new_y));
		env_p->player_x = new_x;
		env_p->player_y = collision_position_y(env_p, new_y);
	}
	else if (!check_collision(env_p, env_p->player_x, new_y))
	{
		count_moves(env_p, collision_position_x(env_p, new_x), new_y);
		env_p->player_x = collision_position_x(env_p, new_x);
		env_p->player_y = new_y;
	}
	else if (touching_x(env_p))
	{
		count_moves(env_p, env_p->player_x,
			collision_position_y(env_p, new_y));
		env_p->player_y = collision_position_y(env_p, new_y);
	}
	else if (touching_y(env_p))
	{
		count_moves(env_p, collision_position_x(env_p, new_x),
			env_p->player_y);
		env_p->player_x = collision_position_x(env_p, new_x);
	}
}

void	move_player(t_mlx_data *env_p)
{
	int	speed;
	int	new_x;
	int	new_y;

	speed = 10;
	new_x = env_p->player_x;
	new_y = env_p->player_y;
	if (env_p->up_pressed)
		new_y -= speed;
	if (env_p->down_pressed)
		new_y += speed;
	if (env_p->left_pressed)
		new_x -= speed;
	if (env_p->right_pressed)
		new_x += speed;
	if (!check_collision(env_p, new_x, new_y))
	{
		count_moves(env_p, new_x, new_y);
		env_p->player_x = new_x;
		env_p->player_y = new_y;
		check_element_collisions(env_p, new_x, new_y);
		return ;
	}
	check_element_collisions(env_p, new_x, new_y);
	move_player_with_collisions(env_p, new_x, new_y);
}
