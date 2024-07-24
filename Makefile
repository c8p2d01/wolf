#OUTPUT NAME
NAME := cub3d

# Folders:
BUILD	= ./build
SOURCE	= ./src

# Other Variables:
COMPILER:=	cc
COMPFLAGS:=	-g #-Wall -Werror -Wextra -Wno-unused-variable 
DEFINES = -D DEBUG=1

# Source Files:
SRCFILES:=\
			main.c \
			raycaster.c \
			utils.c \
			parsing/file_processing.c \
			parsing/map_validation.c \
			parsing/map_variables.c \
			parsing/parse_utils.c \
			parsing/parsing.c \
			parsing/player.c \
			\
			movement/move.c \
			movement/wall_collision.c \


# ------------------------------------------
# Do not change anything beyond this point!
# ------------------------------------------

# Process Variables
CC:=		$(COMPILER)
CFLAGS:=	$(COMPFLAGS)
SRCS:=		$(addprefix $(SOURCE)/,$(SRCFILES))
OBJS:=		$(SRCS:$(SOURCE)/%.c=$(BUILD)/%.o)
NAME:=		./$(NAME)
OS:=		$(shell uname -s)

.PHONY: all clean fclean re e red clear green

LFT = ./ft_libft
MLX = ./MLX42
#-L "/Users/$$USER/.brew/opt/glfw/lib/"
LIBRARYS = -lm -I include -lglfw  $(LFT)/libft.a $(MLX)/libmlx42.a

RED = "\033[38;2;255;51;51m"
GRN = "\033[38;2;170;255;170m"
CLEAR = "\033[0m"

ifeq ($(SUBM_STATE),)
SUBM_FLAG	= submodule
else 
SUBM_FLAG	= 
endif

all: $(SUBM_FLAG) lib
	make -j $(nproc) $(NAME)

submodule: 
	@git submodule init 
	@git submodule update --remote

lib:
	make bonus -C $(LFT)
	make -C $(MLX)

# Compile .cpp files to .o Files
$(OBJS): $(BUILD)%.o : $(SOURCE)%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# Main Build Rule
$(NAME): $(OBJS)
	@echo "--> Compiling Executable"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARYS)

clean:
	@make -s red
	rm -rdf $(BUILD)
	make clean -C $(LFT)
	make clean -C $(MLX)
	@make -s clear

fclean: clean
	@make -s red
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
