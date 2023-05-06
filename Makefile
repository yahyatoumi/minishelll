Name	=	minishell

SRCS	=	main.c ft_split.c ft_strjoin.c ft_strlen.c ft_strtrim.c ft_strdup.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

all:		$(Name)

$(Name):	$(OBJS)
			$(CC) $(CFLAGS) -lreadline -fsanitize=address $(OBJS) -o $(Name)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(Name)

re:			fclean all
