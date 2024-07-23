NAME = cub3d

CC = cc

CFLAGS = #-Wall -Werror -Wextra -g -Wno-unused-variable 

DEFINES = -D DEBUG=1

SD = ./src/
SRC =	main.c \
		input_check.c \
		raycaster.c \
		utils.c \
		minimap.c

#SRC = $(cd src ; find . -name "*.c"; cd -)

SRF = $(addprefix $(SD),$(SRC))

OD = ./obj/
OBJ = $(SRC:.c=.o)
OBF = $(SRF:$(SD)%.c=$(OD)%.o)

LFT = ./ft_libft
MLX = ./MLX42
#-L "/Users/$$USER/.brew/opt/glfw/lib/"
LIBRARYS = -lm -I include -lglfw  $(LFT)/libft.a $(MLX)/libmlx42.a

RED = "\033[38;2;255;51;51m"
GRN = "\033[38;2;170;255;170m"
CLEAR = "\033[0m"

# ifeq ($(SUBM_STATE),)
# SUBM_FLAG	= submodule
# else 
# SUBM_FLAG	= 
# endif

all: $(SUBM_FLAG) lib
	@make -s green
	make $(NAME)
	@make -s clear

submodule: 
	@git submodule init 
	@git submodule update --remote

lib:
	make bonus -C $(LFT)
	make -C $(MLX)

$(OD)%.o: $(SD)%.c
	@mkdir -p $(OD)
	$(CC) $(DEFINES) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBF)
	$(CC) $(DEFINES) $(OBF) -o $(NAME) $(LIBRARYS)

clean:
	@make -s red
	rm -rdf $(OD)
	make clean -C $(LFT)
	make clean -C $(MLX)
	@make -s clear

fclean: clean
	@make -s red
	make fclean -C $(LFT)
	make fclean -C $(MLX)
	rm -rdf $(NAME)
	@make -s clear

re: fclean all

ree: re
	./$(NAME) maps/smol/map.cub

e:
	make
	./$(NAME) maps/smol/map.cub

red:
	echo $(RED)
green:
	echo $(GRN)
clear:
	echo $(CLEAR)

.PHONY: all clean fclean re e red clear green
.SILENT: red clear green
