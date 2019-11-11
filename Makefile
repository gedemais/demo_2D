# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/20 18:40:16 by gedemais          #+#    #+#              #
#    Updated: 2019/11/11 15:58:15 by demaisonc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

OFLAGS = -O3 -Ofast -march=native

SRCS_NAME = main.c\
		deal_key.c\
		math.c\
		load_sprites.c\
		player.c\
		shoot.c\
		mlx_fts.c

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS = $(SRCS_NAME:.c=.o)

MLX_PATH = minilibx_opengl/

MLX = minilibx_opengl/libmlx.a

MLX_OBJS_NAME = mlx_init_loop.o\
				mlx_int_str_to_wordtab.o\
				mlx_new_image.o\
				mlx_new_window.o\
				mlx_shaders.o\
				mlx_xpm.o

MLX_OBJS = $(addprefix $(MLX_PATH), $(MLX_OBJS_NAME))

LIB_PATH = libft/

LIB = libft/libft.a

INC_PATH = includes/

INC = includes/demo.h

NAME = wolf3d

all : $(MLX_PATH) $(LIB) $(NAME) $(INC)

$(NAME) : $(MLX) $(INC) $(LIB_PATH) $(SRCS)
	@echo "Making $(RED)Wolfd3D...$(DEF)"
	$(CC) $(CFLAGS) -o $(NAME) -I $(INC_PATH) -I $(MLX_PATH) $(SRCS) -L $(MLX_PATH) $(MLX) -framework OpenGL -framework AppKit -lpthread $(LIB)
	@echo "$(GRE)Done !$(DEF)"

$(LIB) :
	@echo "Making $(SOU)Libft$(DEF) :"
	@make -C libft/

$(MLX) : $(MLX_PATH)
	@echo "Making $(SOU)MinilibX$(DEF) :"
	@make -C $(MLX_PATH)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(MLX_OBJS)
	@make -C libft/ clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJS)
	@rm -rf $(MLX)
	@make -C libft/ fclean

re : fclean all
