# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stitovsk <stitovsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/25 19:09:12 by stitovsk          #+#    #+#              #
#    Updated: 2024/08/27 17:06:26 by stitovsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
NAME = philo
SRC_DIR = ./src/
BIN_DIR = ./bin/
OBJ_DIR = ./obj/
INC_DIR = ./include/
SRC_FILES = main.c \
			lock_routine.c \
			phil_utils.c \
			start_supper.c \
			supervising.c \
			time_print.c \
			setter_getter.c

OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)%.o)

# Colours
RESET = \033[0;m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m

# Pattern rule to compile .c to .o
# $^ -> current prerequisite name
# $@ -> current target name
%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@
	

all: $(NAME)
	@echo "$(YELLOW)Executable created...$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $^ -o $@
	@echo "$(BLUE)Comiling .o of $@...$(RESET)"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


