# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 12:55:56 by qordoux           #+#    #+#              #
#    Updated: 2024/08/15 20:37:26 by maeferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CFLAGS := -Wall -Werror -Wextra
BUILD_DIR := .build
LIBFT := ./libft
LIBS := ./libft/libft.a
SRC := eat.c free.c init.c main.c think.c threads.c utils.c sleep.c
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(SRC:%.c=$(BUILD_DIR)/%.d)
CC := cc

all: $(LIBFT) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c philosophers.h | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o $(NAME)
	@echo "\033[1;32mPhilo Created!\n"

$(LIBFT)/libft.a : FORCE
	@make -C $(LIBFT)
	@echo "\033[1;32mLibft Created\n"

-include $(DEP)

clean:
	rm -rf $(BUILD_DIR)
	make clean -sC $(LIBFT)

fclean: clean
	rm -f $(NAME) $(LIBS)
	make fclean -C $(LIBFT)

re: fclean all

FORCE:

.PHONY: all clean fclean re