NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
 #MLX_DIR = ./minilibx_mac
MLX_DIR = ./minilibx-linux
LIBFT_DIR = ./libft
GNL_DIR = ./get_next_line

# Libraries
 #MLX = $(MLX_DIR)/libmlx.a -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
MLX = $(MLX_DIR)/libmlx.a -L$(MLX_DIR) -lmlx -lXext -lX11 -lm  #keep only one
LIBFT = $(LIBFT_DIR)/libft.a

# Sources
SRC = main.c init.c free.c \
	  parsing/elements.c parsing/file_utils.c parsing/map_utils.c \
	  parsing/parse_map.c parsing/validate_map.c parsing/store_map.c \
	  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

# Include paths
INCLUDES = -Iinc -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)

# Build rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
