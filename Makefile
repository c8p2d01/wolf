#OUTPUT NAME
NAME := cub3D

# Folders:
BUILD	= ./build
SOURCE	= ./src

# Other Variables:
COMPILER:=	cc
COMPFLAGS:=	-g #-fsanitize=address #-Wall -Werror -Wextra -Wno-unused-variable 
DEFINES = -D DEBUG=1

# Source Files:
SRCFILES:=\
			main.c \
			utils.c \
			hook_functions.c \
			initialisation.c \
			\
			minimap/map_plane.c \
			minimap/draw_triangle.c \
			minimap/ray_marcher.c \
			minimap/draw_mini_rays.c \
			\
			parsing/player.c\
			parsing/file_processing.c \
			parsing/map_validation.c \
			parsing/flood_iterative.c \
			parsing/map_separation.c \
			parsing/map_line_validation.c \
			parsing/map_variables.c \
			parsing/map_variables_ext.c \
			parsing/parse_utils.c \
			parsing/parse_utils2.c \
			parsing/parsing.c \
			\
			movement/mouse.c \
			movement/move.c \
			movement/wall_collision.c \
			\
			rendering/floor_ceiling.c \
			rendering/slicer.c \
			rendering/doors.c \
			rendering/raycaster.c \
			\
			settings/print_settings.c \
			settings/settings_1.c \
			settings/settings_2.c \
			settings/settings_3.c \
			settings/settings_utils.c \
			\
			gifdecoder/gif_basics.c \
			gifdecoder/open_gif.c \
			gifdecoder/gif_read_image.c \
			gifdecoder/gif_read_opt.c \
			gifdecoder/gif_table.c \
			gifdecoder/gif_frame.c \
			gifdecoder/utils.c \




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
LIBMLX = ./MLX42
LIBRARYS	:= $(LFT)/libft.a
ifeq ($(shell uname),Darwin)
	LIBRARYS += $(LIBMLX)/libmlx42.a -framework OpenGL -framework IOKit -lglfw
else ifeq ($(shell uname),Linux)
	LIBRARYS += $(LIBMLX)/libmlx42.a -Iinc -Ilib/libft -ldl -lglfw3 -pthread -lm
endif
RED = "\033[38;2;255;51;51m"
GRN = "\033[38;2;170;255;170m"
CLEAR = "\033[0m"

# ifeq ($(SUBM_STATE),)
# SUBM_FLAG	= submodule
# else 
# SUBM_FLAG	=
# endif

all: $(SUBM_FLAG) lib
	make -j $(nproc) $(NAME)

submodule: 
	@git submodule init
	@git submodule update --remote --init --recursive
	@cmake -S $(LIBMLX) -B $(LIBMLX)

lib:
	make bonus -C $(LFT)
	make -C $(LIBMLX)

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
	make clean -C $(LIBMLX)
	@make -s clear

fclean:
	@make -s red
	rm -rdf $(NAME)
	rm -rdf $(BUILD)
	make fclean -C $(LFT)
	make clean -C $(LIBMLX)
	@make -s clear

re: fclean all

ree: re
	./$(NAME) maps/subject.cub

e:
	make
	./$(NAME) maps/subject.cub

red:
	echo $(RED)
green:
	echo $(GRN)
clear:
	echo $(CLEAR)

.PHONY: all clean fclean re e red clear green
.SILENT: red clear green
# export DISPLAY=:99 && Xvfb :99 -screen 0 1024x768x16 & vgf ./cub3D test.cub & sleep 1 && xdotool search --name "cub3D" key w && sleep 1 && xdotool search --name "cub3D" key right && sleep 1 && xdotool search --name "cub3D" key escape