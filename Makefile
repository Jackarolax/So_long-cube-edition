# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 09:33:26 by anematol          #+#    #+#              #
#    Updated: 2025/08/14 13:10:13 by anematol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR = ./minilibx-linux

MLX_REPO = https://github.com/42Paris/minilibx-linux.git

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

CFILES =	main.c\
			hook_functions.c \
			map.c \
			map_get.c \
			map_validate_basics.c \
			map_validate_path.c \
			draw_background.c \
			draw_elements.c \
			element_collision.c \
			movement.c \
			movement_collision_checking.c \
			image_functions.c \
			load_sprite.c \
			./get_next_line/get_next_line_utils.c\
			./get_next_line/get_next_line.c\
			./ft_printf/ft_printf_c.c \
			./ft_printf/ft_printf_i.c \
			./ft_printf/ft_printf_p.c \
			./ft_printf/ft_printf_s.c \
			./ft_printf/ft_printf_u.c \
			./ft_printf/ft_printf_x.c \
			./ft_printf/ft_printf.c \


OFILES =	main.o\
			hook_functions.o \
			map.o \
			map_get.o \
			map_validate_basics.o \
			map_validate_path.o \
			draw_background.o \
			draw_elements.o \
			element_collision.o \
			movement.o \
			movement_collision_checking.o \
			image_functions.o \
			load_sprite.o \
			get_next_line_utils.o\
			get_next_line.o \
			./ft_printf_c.o \
			./ft_printf_i.o \
			./ft_printf_p.o \
			./ft_printf_s.o \
			./ft_printf_u.o \
			./ft_printf_x.o \
			./ft_printf.o \

INCLUDES = so_long.h

NAME = so_long

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR) > /dev/null

$(OFILES): $(CFILES) $(INCLUDES)
		cc $(CFLAGS) -c $(CFILES)

$(NAME): $(OFILES)
		cc $(CFLAGS)  $(OFILES) -o $(NAME) $(MLX_FLAGS)

clean:
		rm -f $(OFILES)

fclean: clean
		rm -f $(NAME)

re: fclean all
