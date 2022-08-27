# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:58:48 by tmoragli          #+#    #+#              #
#    Updated: 2022/08/27 20:34:46 by nargouse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------- EXECUTABLE -----------

NAME		=	cub3D
DESCRIPTION =	Cub3D project for [42]

# ----------- INCLUDE --------------

INCLUDE		=	./includes/

# ------------ LIB -----------------

MLX	= ./mlx/libmlx.a
LIBFT	= ./libft/libft.a
LIB	= $(MLX) $(LIBFT)

# ----------- COMPILER FLAGS -------

CC			=	clang
CFLAGS		+=	-Wall -Wextra -Werror -g3
LFLAGS		=	-Lmlx -lbsd -lXext -lX11 -lmlx -lm

# ----------- FILES ----------------

SRC			=	./srcs
OBJ			=	./objs
SRCS		=	$(SRC)/main.c					\
				$(SRC)/check_av.c				\
				$(SRC)/cub_start.c				\
				$(SRC)/draw.c					\
				$(SRC)/exit_game.c				\
				$(SRC)/fill_map.c				\
				$(SRC)/get_rgb.c				\
				$(SRC)/init_game.c				\
				$(SRC)/key_hook.c				\
				$(SRC)/malloc_data.c			\
				$(SRC)/maths.c					\
				$(SRC)/moves.c					\
				$(SRC)/parse_colors.c			\
				$(SRC)/parse_id.c 				\
				$(SRC)/parse_map.c				\
				$(SRC)/parse_textures.c			\
				$(SRC)/parsing_checks.c			\
				$(SRC)/raycasting.c				\
				$(SRC)/rays.c					\
				$(SRC)/setup_rays.c				\
				$(SRC)/init_subdata.c			\
				$(SRC)/rescale_size.c			\
				$(SRC)/check_colors.c			\
				$(SRC)/parsing_checks2.c		\
				$(SRC)/draw2.c					\
				$(SRC)/change_player_pos.c		\
				$(SRC)/start_game.c
				
SRCS_BONUS	=	$(SRC)/main.c					\
				$(SRC)/check_av.c				\
				$(SRC)/cub_start.c				\
				$(SRC)/draw.c					\
				$(SRC)/exit_game.c				\
				$(SRC)/fill_map.c				\
				$(SRC)/get_rgb.c				\
				$(SRC)/init_game.c				\
				$(SRC)/key_hook_bonus.c			\
				$(SRC)/malloc_data.c			\
				$(SRC)/maths.c					\
				$(SRC)/moves.c					\
				$(SRC)/parse_colors.c			\
				$(SRC)/parse_id.c 				\
				$(SRC)/parse_map.c				\
				$(SRC)/parse_textures.c			\
				$(SRC)/parsing_checks.c			\
				$(SRC)/raycasting.c				\
				$(SRC)/rays.c					\
				$(SRC)/setup_rays.c				\
				$(SRC)/init_subdata.c			\
				$(SRC)/rescale_size.c			\
				$(SRC)/check_colors.c			\
				$(SRC)/parsing_checks2.c		\
				$(SRC)/draw2.c					\
				$(SRC)/start_game.c				\
				$(SRC)/change_player_pos_bonus.c
				
				
OBJS		= $(patsubst $(SRC)/%.c, $(OBJ)/%.o,$(SRCS))
OBJS_BONUS	= $(patsubst $(SRC)/%.c, $(OBJ)/%.o,$(SRCS_BONUS))

# ----------- COLORS ---------------

BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
PURPLE		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
BLUE		= \033[0;34m
EOC			= \033[0;0m

# ----------- RULES ----------------

all			: $(NAME)

bonus		: $(NAME)_bonus

${NAME}		: $(MLX) $(LIBFT) $(OBJS)
	@echo "$(BLUE) =========> Compiling object files <========="
	@echo "$(WHITE)"
		$(CC) $(OBJS) $(LIB) $(CFLAGS) $(LFLAGS) -o $@
	@echo "$(BLUE) =====> Build $(DESCRIPTION) DONE √ <====="
	@echo -n "$(EOC)"

${NAME}_bonus	: $(MLX) $(LIBFT) $(OBJS_BONUS)
	@echo "$(BLUE) =========> Compiling object files <========="
	@echo "$(WHITE)"
		$(CC) $(OBJS_BONUS) $(LIB) $(CFLAGS) $(LFLAGS) -o $@
	@echo "$(BLUE) =====> Build $(DESCRIPTION) DONE √ <====="
	@echo -n "$(EOC)"

$(OBJ)/%.o	: $(SRC)/%.c
	@echo -n "$(PURPLE)"
		mkdir -p ./objs/
		$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(MLX):
	@echo "$(BLUE) =========> Compiling MLX library <========="
	@echo "$(CYAN)"
		$(MAKE) -C ./mlx
	@echo -n "$(EOC)"

$(LIBFT):
	@echo "$(BLUE) =========> Compiling LIBFT library <========="
	@echo "$(CYAN)"
		$(MAKE) --no-print-directory -C ./libft
	@echo -n "$(EOC)"

clean		:
	@echo "$(BLUE) =========> Deleting object files <========="
	@echo "$(PURPLE)"
		$(MAKE) -C ./mlx clean
		$(MAKE) -C ./libft clean
		$(RM) $(OBJS)
	    $(RM) $(OBJS_BONUS)	

fclean		: clean
	@echo "$(BLUE) =========> Deleting executable <========="
	@echo "$(PURPLE)"
		$(RM) $(NAME)
		$(RM) $(NAME)_bonus
	@echo "$(GREEN)"
		$(RM) $(MLX)
		$(RM) $(LIBFT)
	@echo "$(BLUE) =====> Cleaning LIBFT and MLX DONE √ <====="
re			: fclean all

norm		:
	@echo "$(BLACK)"
		norminette $(LIBFT)
	@echo "$(CYAN)"
		norminette $(SRC) $(INCLUDE)
	@echo "$(BLUE) =====> Checking the norminette DONE √ <====="

.PHONY: all clean fclean re norm
