SRCS	= main.c \
		utils.c \
		parsing.c \
		thread_func.c \
		activities.c \
		philosophers.c \
		check.c \

# -fsanitize=thread 
OBJS			= $(SRCS:.c=.o)

CC				= gcc 
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror  -fsanitize=thread  -I.
LIBS			= -lpthread

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS}  -o ${NAME} ${OBJS}   ${LIBS}


clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
