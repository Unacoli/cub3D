# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:58:48 by tmoragli          #+#    #+#              #
#    Updated: 2022/08/09 18:58:30 by tmoragli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------- EXECUTABLE -----------
NAME		=	cub3D
DESCRIPTION =	Cub3D

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
SRCS		=	$(SRC)/main.c
OBJS		= $(patsubst $(SRC)%.c, $(OBJ)/%.o,$(SRCS))

# ----------- COLORS ---------------
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
PURPLE		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
EOC			= \033[0;0m

# ----------- RULES ----------------
all			: $(NAME)
${NAME}		: $(OBJS)
	@echo "$(RED) =========> Compiling object files.............DONE √\n"
	@echo "$(WHITE)"
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LPFLAGS) -o $@
	@echo "$(RED) =========> Building $(DESCRIPTION).............DONE √\n"
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
	@echo "$(PURPLE)"
			-rm -rf $(OBJ)
	@echo "$(RED) =========> Deleting object files.............DONE √\n"

fclean		: clean
	@echo "$(PURPLE)"
			-rm -f $(NAME)
	@echo "$(RED) =========> Deleting executable................DONE √\n"
	@echo "$(GREEN)"
			make fclean -C $(LIBFT)
			make clean -C $(MLX)
	@echo "$(RED) =========> Cleaning libft and mlx.............DONE √\n"

re			: fclean all

norm		:
	@echo "$(BLACK)"
			norminette $(LIBFT)
	@echo "$(CYAN)"
			norminette $(SRC) $(INCLUDE)
	@echo "$(RED) =========> Checking the norminette............DONE √\n"

.PHONY: all clean fclean re norm