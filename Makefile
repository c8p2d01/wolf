NAME = Termi_3D

CC = cc

CFLAGS = #-Wall -Werror -Wextra -g -Wno-unused-variable

DEFINES = -D DEBUG=100

SD = ./src/
SRC =	main.c \
		raycaster.c

SRF = $(addprefix $(SD),$(SRC))

OD = ./obj/
OBJ = $(SRC:.c=.o)
OBF = $(SRF:$(SD)%.c=$(OD)%.o)

all: $(NAME)

$(OD)%.o: $(SD)%.c
	@mkdir -p $(OD)
	$(CC) $(CFLAGS) $(DEFINES) -c -o $@ $<

$(NAME): $(OBF)
	$(CC) $(OBF) $(DEFINES) -o $(NAME)
clean:
	rm -rdf $(OD)

fclean: clean
	rm -rdf $(NAME)

re: fclean all

e: re
	./$(NAME)

phony: all clean fclean re e
