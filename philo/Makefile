# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 12:55:56 by qordoux           #+#    #+#              #
#    Updated: 2024/08/27 20:32:47 by maeferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
STANDARD_FLAGS = -Wall -Wextra -Werror
BUILD_DIR := .build
SRC_DIR = ./src/
SRCS_FILES = eat.c free.c init.c main.c think.c threads.c utils.c sleep.c
OBJ_FILES = $(SRCS_FILES:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean fclean re

all: ${NAME}

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(NAME) : $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES)

$(BUILD_DIR)/%.o : %.c philosophers.h | $(BUILD_DIR)
	$(CC) $(STANDARD_FLAGS) -o $@ -c $<

clean: clean
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: clean all 