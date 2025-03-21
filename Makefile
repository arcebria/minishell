# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by arcebria          #+#    #+#              #
#    Updated: 2025/03/19 20:48:21 by arcebria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c) 
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

INCLUDE = inc/minishell.h libft/libft.h libft/ft_printf.h

all: dir $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) Makefile
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -o $(NAME) -lreadline
		@echo "\033[31mPLVS VLTRA\033[0m"

dir:
	@make -C $(LIBFT_DIR) --silent

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean --silent
	@rm -rf $(OBJ_DIR)
	@echo "\033[31mNON PLVS VLTRA\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
