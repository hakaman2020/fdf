# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: hman <hman@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/22 14:20:49 by hman          #+#    #+#                  #
#    Updated: 2021/09/06 15:46:32 by hman          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
NAME = fdf
UNAME = $(shell uname -s)

# libraries
LIB_DIR = lib
LIB_FLAGS = $(MLX_FLAGS) $(LIBFT_FLAGS) $(OTHER_FLAGS)

# libft library
LIBFT_DIR = libft
LIBFT_FLAGS = -L$(LIB_DIR)/$(LIBFT_DIR) -lft

# graphics library mlx and math library
ifeq ($(UNAME), Darwin)
	MLX_FLAGS = -L./$(LIB_DIR)/mlx -lmlx
	OTHER_FLAGS = -framework OpenGL -framework Appkit 
	OS_FLAG = -DLINUX=0
endif
ifeq ($(UNAME), Linux)
	MLX_FLAGS = -L./$(LIB_DIR)/mlx_linux -lmlx_Linux
	OTHER_FLAGS = -lX11 -lXext -lm 
	OS_FLAG = -DLINUX=1
endif

#source code
SRC_DIR = src
SRC_FILES = $(addprefix $(SRC_DIR)/,\
	fdf.c \
	fdf_parser.c \
	fdf_scan_map.c \
	errors.c \
	fdf_init_iso.c \
	fdf_key_press.c \
	fdf_isometric_ops.c \
	fdf_image_ops.c \
	fdf_bres_algo.c \
	get_next_line.c \
	get_next_line_utils.c)

#object files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIB_FLAGS)  

bonus : $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
#	@$(info $(shell mkdir -p obj))
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ $(OS_FLAG) 

clean:
	$(MAKE) -C ./lib/libft clean
	rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) -C ./lib/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
