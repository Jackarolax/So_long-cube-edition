/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:10:20 by anematol          #+#    #+#             */
/*   Updated: 2025/12/05 17:02:44 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include "./get_next_line/get_next_line.h"
# include "./ft_printf/ft_printf.h"
# include <sys/time.h>

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_mlx_data
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	int				up_pressed;
	int				down_pressed;
	int				left_pressed;
	int				right_pressed;
	long int		up_counter;
	long int		down_counter;
	long int		left_counter;
	long int		right_counter;
	int				player_x;
	int				player_y;
	int				collectible_count;
	struct timeval	t0;
	struct timeval	t1;
	t_image			buffer_img;
	t_image			background_img;
	t_image			player_img;
	t_image			wall_img;
	t_image			collectible_img;
	t_image			exit_closed_img;
	t_image			exit_open_img;
	int				block_size;
	int				map_height;
	int				map_width;
	char			**map;
}				t_mlx_data;

//hook_functions.c
int		close_window(void *param);
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);
int		update_game(void *param);
//map.c
void	free_map(t_mlx_data *env_p);
int		get_map(t_mlx_data *env_p, char *map_filepath);
int		load_map(t_mlx_data *env_p, char *map_filepath);
//map_validate_basics.c
int		validate_elements(t_mlx_data *env_p);
int		validate_walls(t_mlx_data *env_p);
int		validate_map(t_mlx_data *env_p);
void	error_msg(char *msg);
int		check_file_extension(char *map_filepath, char *extension);
//map_validate_path.c
int		validate_obtainability(t_mlx_data *env_p);
void	renew_map(t_mlx_data *env_p);
//draw_elements.c
void	draw_obstacles(t_mlx_data *env_p);
void	draw_collectibles(t_mlx_data *env_p);
void	draw_exit(t_mlx_data *env_p, int open);
//test.c
void	destroy_everything_and_exit(t_mlx_data *env_p, int exit_code);
void	put_pixel_to_image(t_image image, int x, int y, int color);
int		draw_to_window(void *param);
//movement.c
void	move_player(t_mlx_data *env_p);
//background.c
void	copy_background_to_buffer(t_mlx_data *env_p);
int		create_background(void *param);
//image_functions.c
int		get_img_pixel(t_image image, int x, int y);
void	put_pixel_to_image(t_image image, int x, int y, int color);
void	put_img_inside_img(t_image small_image,
			t_image large_image, int x, int y);
//load_sprite.c
void	load_sprite(t_mlx_data *env_p, t_image *image_p, char *path);

int		check_collision(t_mlx_data *env_p, int check_x, int check_y);
int		collision_position_x(t_mlx_data *env_p, int new_x);
int		collision_position_y(t_mlx_data *env_p, int new_y);
int		touching_x(t_mlx_data *env_p);
int		touching_y(t_mlx_data *env_p);

//element_collision.c
void	check_element_collisions(t_mlx_data *env_p, int new_x, int new_y);

int		ft_strcmp(const char *s1, const char *s2);
#endif
