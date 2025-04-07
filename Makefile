# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 20:05:41 by arcebria          #+#    #+#              #
#    Updated: 2025/03/27 12:23:25 by aguinea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
#                             COMPILATION & MORE                               #
################################################################################

NAME		= minishell
NAME_BONUS = minishell_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
DEPFLAGS	= -MMD -MF $(DEPDIR)/$*.d
INCLUDE		= -Iinc -Ilibft



################################################################################
#                                 PATH/TO/SRCS                                 #
################################################################################

SRCDIR		= src

OBJDIR		= obj

DEPDIR		= deps

LIBFT_DIR	= libft

INCLUDE_DIR	= inc

################################################################################
#                           SRCS & OBJS & DEPS                                 #
################################################################################


LIBFT_A		= $(LIBFT_DIR)/libft.a

HEADER		= $(INCLUDE_DIR)/minishell.h
HEADER_BONUS		= $(INCLUDE_DIR)/minishell_bonus.h
HEAD_LIBFT	= $(LIBFT_DIR)/libft.h
ALL_HEADERS	= $(HEADER) $(HEAD_LIBFT)
ALL_HEADERS_BONUS	= $(HEADER_BONUS) $(HEAD_LIBFT)


SRCS 		= src/main/main.c src/init/init_env.c src/init/tokenizer.c 				\
       		src/init/parser.c src/init/syntax_analize.c src/init/parse_cmd.c 		\
			src/setup_exec/open_files.c src/setup_exec/setup_heredoc.c src/setup_exec/expand_heredoc.c src/setup_exec/setup_shell.c	\
       		src/exec/exec_cmd.c src/exec/make_dup.c  src/exec/set_dup.c src/exec/manage_heredoc.c src/exec/check_builtins.c	\
			src/exec/mini_cd.c src/exec/mini_env_echo_pwd.c src/exec/mini_unset_export.c src/exec/minicd_utils.c							\
       		src/clean_free/clean_fds.c 	src/clean_free/free_structs.c src/clean_free/put_errors.c		\
       		#src/others/signals.c
OBJS 		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS 		= $(OBJS:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

SRCS_BONUS 		= src/main/main_bonus.c src/init/init_env.c src/init/tokenizer_bonus.c src/init/wildcard_bonus.c 				\
       		src/init/parser.c src/init/syntax_analize.c src/init/parse_cmd.c 		\
			src/setup_exec/open_files.c src/setup_exec/setup_heredoc.c src/setup_exec/expand_heredoc.c src/setup_exec/setup_shell.c	\
       		src/exec/exec_cmd.c src/exec/make_dup.c  src/exec/set_dup.c src/exec/manage_heredoc.c src/exec/check_builtins.c	\
			src/exec/mini_cd.c src/exec/mini_env_echo_pwd.c src/exec/mini_unset_export.c src/exec/minicd_utils.c							\
       		src/clean_free/clean_fds.c 	src/clean_free/free_structs.c src/clean_free/put_errors.c		\
       		#src/others/signals.c
OBJS_BONNUS 		= $(SRCS_BONUS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS_BONUS 		= $(OBJS_BONNUS:$(OBJDIR)/%.o=$(DEPDIR)/%.d)


################################################################################
#                              MAKEFILE RULES                                  #
################################################################################


all				: dir $(LIBFT_A) $(NAME)

bonus		: $(LIBFT_A) dir $(NAME_BONUS)

$(NAME_BONUS)	: $(OBJS_BONNUS) $(LIBFT_A)
				@$(CC) $(CFLAGS) $(OBJS_BONNUS) $(LIBFT_A) -o $(NAME_BONUS) -lreadline
				@echo "\033[32mPLVS VLTRA BONUS\033[0m"

$(OBJDIR)/%_bonus.o	: $(SRCDIR)/%_bonus.c $(ALL_HEADERS_BONUS) | dir
				@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@


$(NAME)			: $(OBJS) $(LIBFT_A) Makefile
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lreadline
				@echo "\033[31mPLVS VLTRA\033[0m"

dir				:
				@mkdir -p $(OBJDIR) $(DEPDIR) $(dir $(OBJS)) $(dir $(DEPS))

$(LIBFT_A)		:
				@make -C $(LIBFT_DIR) --silent

$(OBJDIR)/%.o	: $(SRCDIR)/%.c $(ALL_HEADERS) | dir
				@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

clean			:
				@make -C $(LIBFT_DIR) clean --silent
				@rm -rf $(OBJDIR) $(DEPDIR)
				@echo "\033[31mNON PLVS VLTRA\033[0m"

fclean			: clean
				@make -C $(LIBFT_DIR) fclean --silent
				@rm -f $(NAME) $(NAME_BONUS)

re				: fclean all

-include $(DEPS)

.PHONY: all clean fclean re dir
