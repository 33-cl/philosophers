# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: debian <debian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 12:55:56 by qordoux           #+#    #+#              #
#    Updated: 2024/07/09 03:06:15 by debian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philosophers
CFLAGS := 
BUILD_DIR := .build
LIBFT := ./libft
LIBS := ./libft/libft.a
SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(SRC:%.c=$(BUILD_DIR)/%.d)
CC := cc

all: $(LIBFT) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(CFLAGS) -lreadline -o $(NAME)
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