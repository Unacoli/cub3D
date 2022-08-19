# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 23:30:16 by tmoragli          #+#    #+#              #
#    Updated: 2022/08/12 00:01:48 by tmoragli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------- LIBRARY --------------
NAME		= libft.a

# ----------- COMPILER FLAGS -------
CC			= clang
CFLAGS		+= -Wall -Wextra -Werror

# ----------- FILES ----------------
INCLUDE		= ./include
OBJ			= ./objs
SRC			= ./srcs
SRCS_MEM	=	ft_swap_str.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c
SRCS_STR	=	ft_strchr.c ft_strdup.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_strlen.c ft_error.c str_arr_display.c str_arr_free.c str_arr_size.c
SRCS_PUTFD	=	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS_IS		=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_isspace.c
SRCS_TO		=	ft_atoi.c ft_itoa.c 
SRCS_MALLOC	=	ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_malloc.c ft_free_tab.c
SRCS_PRINTF =	ft_printf.c ft_parsing.c ft_putnbr_base.c ft_putnbr_base_2.c ft_hex.c ft_u.c ft_d_i.c ft_utils.c ft_p.c ft_s.c
SRCS_GNL	=	get_next_line.c
SRCS_LST	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
SRCS		=	${SRCS_MEM} ${SRCS_STR} ${SRCS_PUTFD} ${SRCS_IS} ${SRCS_TO} ${SRCS_MALLOC} ${SRCS_PRINTF} ${SRCS_LST} ${SRCS_GNL}

OBJS		= $(patsubst %.c, $(OBJ)/%.o,$(SRCS))

# ----------- RULES ----------------
all		: ${NAME}
$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}

$(OBJ)/%.o	: $(SRC)/%.c | $(OBJ)
	$(CC) -I $(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ)		:
	mkdir $@
	
bonus	: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean	:
	rm -rf ${OBJ}

fclean	:	clean
	rm -rf ${NAME}

re		:	fclean all

.PHONY	: all clean fclean re bonus
