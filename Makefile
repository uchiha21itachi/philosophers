SRCS	= main.c \
		utils.c \
		thread_func.c \
		philosophers.c \


OBJS			= $(SRCS:.c=.o)

CC				= gcc #-g -fsanitize=thread
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.  
LIBS			= -lpthread

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS} 


clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
