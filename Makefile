CC = cc
CFLAGS = -g -Wall -Wextra -Werror -MMD -MP
NAME = cub3D
CFLAGS_RD = -lreadline

# MiniLibX configuration
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Libft configuration
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE = -I./include

# Source files
SRC_PATH = src
OBJ_DIR = build


SRC_FILES = main.c \
			draw.c \
			raycasting.c \
			check_map.c \
			move.c \
			init.c \
			set_player_direction.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			\
			parsing/parsing.c \
			\
			exit/exit_program.c \
			exit/free_all.c \
			exit/print_error.c \


SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
DEPS = $(OBJ:.o=.d)

LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)
LIBFT_HDR = $(LIBFT_DIR)/libft.h

# Colors
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

MAKEFLAGS += --no-print-directory

.PHONY: all clean fclean re mlx_check mlx_clone mlx_build ext

all: mlx_check $(NAME)

# MiniLibX rules
mlx_clone:
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "MiniLibX absente, clonage depuis GitHub..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi

mlx_build:
	@if [ ! -f $(MLX_LIB) ]; then \
		echo "Compilation MiniLibX..."; \
		$(MAKE) -C $(MLX_DIR); \
	fi

mlx_check: mlx_clone mlx_build

# Main compilation
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS_RD) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)The program is ready !$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LIBFT_INCLUDE) -I$(MLX_DIR) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_HDR)
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)Object files deleted.$(RESET)"

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@if [ -d $(MLX_DIR) ]; then \
		echo "Suppression complète de MiniLibX..."; \
		rm -rf $(MLX_DIR); \
	fi
	@echo "$(RED)Executable and object files deleted.$(RESET)"

re: fclean all

# Force MiniLibX recompilation
ext:
	@if [ -d $(MLX_DIR) ]; then \
		echo "Recompilation forcée MiniLibX..."; \
		$(MAKE) -C $(MLX_DIR) clean; \
		$(MAKE) -C $(MLX_DIR); \
	else \
		$(MAKE) mlx_clone mlx_build; \
	fi

-include $(DEPS)
