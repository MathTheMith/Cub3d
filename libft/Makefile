# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 13:56:20 by tfournie          #+#    #+#              #
#    Updated: 2025/11/17 15:41:52 by tfournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -MMD -MP
NAME = libft.a
INCLUDE_PATH = -I.

SRC_FILES = 	ft_atoi.c \
				ft_atoll.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_is_valid_number.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strcpy.c \
				ft_strcmp.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_substr.c \
				ft_strtrim.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strstr.c \
				ft_realloc.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \

SRC_PATH = functions
OBJ_DIR = obj


SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
DEPS = $(OBJ:.o=.d)

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

MAKEFLAGS += --no-print-directory

all: $(NAME)

objdir:
	mkdir -p $(OBJ_DIR)

$(OBJ): | objdir

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "${GREEN}libft.a was created with success !${RESET}"

$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c libft.h Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@echo "${RED}File object of the libt were created.${RESET}"

fclean: clean
	rm -f $(NAME)
	@echo "${RED}libft.a was deleted.${RESET}"

re: fclean all

.PHONY: all clean fclean re objdir

-include $(DEPS)


