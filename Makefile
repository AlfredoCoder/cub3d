# Variáveis
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
SRC = src/main.c \
        src/render.c \
	src/pixels.c \
	src/comands.c \
	src/moviment.c \
	src/moviment_utils.c \
	src/textures.c \
	src/textures_draw.c \
	src/textures_load.c \
        src/parsing.c \
        src/player_utils.c \
        src/player_dir.c \
        src/utils.c
OBJ = $(SRC:.c=.o)
NAME = cub3D
LIBFT_PATH = lib
PATH_LIBS = -L$(LIBFT_PATH)
LIBS = -lreadline -lft

# Regras
all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_PATH)/libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) $(PATH_LIBS) $(LIBS)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	make clean -C $(MLX_DIR)
	make fclean -C $(LIBFT_PATH)

re: fclean all



