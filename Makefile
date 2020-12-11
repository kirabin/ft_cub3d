# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmilan <dmilan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 19:40:30 by dmilan            #+#    #+#              #
#    Updated: 2020/12/11 15:19:16 by dmilan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
FLAGS		=	-Wall -Wextra #-Werror
LIBFT		=	libft/libft.a

SRC			=	cub3d.c \
				draw.c \
				raycasting.c \
				bindings.c \
				map.c \
				map_validate.c \
				map_parce.c

OBJ			= $(SRC:.c=.o)
INC_DIRS	=  -I. -I./libft -I./mlx_opengl
HEADERS		= cub3d.h libft/libft.h
MLX_OG		= -framework OpenGL -framework AppKit -Lmlx_opengl/ -lmlx
MLX_MM		= -framework OpenGL -framework AppKit -L. -lmlx


all: $(NAME)

$(LIBFT): 
	make -C libft

%.o: %.c $(HEADERS)
	 gcc $(FLAGS) $(INC_DIRS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ) $(INC)
	# make -C mlx_opengl
	# mv mlx_opengl/libmlx.dylib libmlx.dylib
	gcc -g $(FLAGS) $(SRC) $(MLX_OG) -L./libft -lft -o $(NAME) $(INC_DIRS)    #remove SRC and -g

clean:
	# mv libmlx.dylib mlx_mms/libmlx.dylib
	# make clean -C mlx_mms; cd ..
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

run:
	./$(NAME) levels/default.cub
	
save:
	./$(NAME) --save