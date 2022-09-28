NAME = Terminal3d

SRC =	main.c

OBJ	=	${SRC:.c=.o}

CC = gcc

HEADERS = cub.h

CFLAGS = -Wall -Wextra -Werror

#.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $@  -lm

%.o: %.c $(HEADER_FILES)
	$(CC) -c -Wall -Werror -Wextra -o $@ $<

e: all
	./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re e
