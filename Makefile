CC = cc

CFLAGS = -Werror -Wall -Wextra -pthread

NAME = codexion

SRCS = main.c parser.c
OBJ = $(SRCS:.c=.o)

HEADER = header.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re


