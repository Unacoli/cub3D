# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:58:48 by tmoragli          #+#    #+#              #
#    Updated: 2022/08/10 02:09:53 by tmoragli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------- EXECUTABLE -----------
NAME		=	cub3d
DESCRIPTION =	Cub3D project for [42]

# ----------- COMPILER FLAGS -------
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
LPFLAGS		=	-L$(LIBFT) -Lmlx -lbsd -lXext -lX11 -lmlx -lm

# ----------- INCLUDE --------------
INCLUDE		=	includes
INCLUDES	=	-I $(INCLUDE) -I $(LIBFT) -I $(MLX)

# ----------- FILES ----------------
SRC			=	./srcs
OBJ			=	./objs
LIBFT		=	./libft
MLX			=	./mlx
SRCS		=	$(SRC)/main.c								\
				$(SRC)/draw.c
OBJS		= $(patsubst $(SRC)%.c, $(OBJ)/%.o,$(SRCS))

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
${NAME}		: $(OBJS)
	@echo "$(BLUE) =========> Compiling object files <========="
	@echo "$(WHITE)"
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LPFLAGS) -o $@
	@echo "$(BLUE)            Build $(DESCRIPTION) DONE √"
$(OBJ)/%.o	: $(SRC)/%.c | $(OBJ) compiling
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

compiling	:
			@echo -n "$(WHITE)"

$(OBJ)		:
	@echo "$(PURPLE)"
			mkdir $@
	@echo "$(GREEN)"
			make -C $(LIBFT)
			make -C $(MLX)

clean		:
	@echo "$(BLUE) =========> Deleting object files <========="
	@echo "$(PURPLE)"
			-rm -rf $(OBJ)

fclean		: clean
	@echo "$(BLUE) =========> Deleting executable <========="
	@echo "$(PURPLE)"
			-rm -f $(NAME)
	@echo "$(GREEN)"
			make fclean -C $(LIBFT)
			make clean -C $(MLX)
	@echo "$(BLUE)            Cleaning LIBFT and MLX DONE √"

re			: fclean all

norm		:
	@echo "$(BLACK)"
			norminette $(LIBFT)
	@echo "$(CYAN)"
			norminette $(SRC) $(INCLUDE)
	@echo "$(BLUE)            Checking the norminette DONE √"

.PHONY: all clean fclean re norm