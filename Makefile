NAME	=	philo

SRCS	=	main.c \
			utils.c \
			parser.c \
			threads.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread -fsanitize=thread -g

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

debug:		$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)
			rm -rf .*.swp

re:			fclean all

.PHONY:		all clean fclean re
