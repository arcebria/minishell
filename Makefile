# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by arcebria          #+#    #+#              #
#    Updated: 2025/01/28 19:08:51 by arcebria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

INCLUDE = libft/libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address	


all: dir $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) Makefile
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)
		@echo "\033[31mPLVS VLTRA\033[0m"

dir:
	@make -C $(LIBFT_DIR) --silent

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean --silent
	@rm -f $(OBJS)
	@echo "\033[31mNON PLVS VLTRA\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
