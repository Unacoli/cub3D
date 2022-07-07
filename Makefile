NAME	= name
INCLUDE = ./include/
LIBFT	= ./libft/libft.a
CFLAGS	+= -Wall -Werror -Wextra

FILES	= main.c 

SRCS	= $(addprefix ./srcs/, $(FILES))
OBJS	= $(addprefix ./objs/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -o $@

objs/%.o: srcs/%.c
	mkdir -p ./objs/
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(LIBFT):
	$(MAKE) --no-print-directory -C ./libft

clean:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJS) 

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re:	fclean all

.PHONY:	all clean fclean re
