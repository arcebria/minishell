################################################################################
#                              CONFIGURATION                                   #
################################################################################

NAME				= minishell
NAME_BONUS	= minishell_bonus

CC					= cc
CFLAGS			= -Wall -Wextra -Werror -g
DEPFLAGS		= -MMD -MF $(DEPDIR)/$*.d
LDFLAGS			= -lreadline # para trabajar desde casa

INCLUDE			= -Iinc -Ilibft -I/usr/include

SRCDIR			= src
OBJDIR			= obj
DEPDIR			= deps
LIBFT_DIR		= libft

################################################################################
#                              SOURCE FILES                                    #
################################################################################

SRCS = \
	src/main/main.c \
	src/init/init_env.c \
	src/init/tokenizer.c \
	src/init/parser.c \
	src/init/syntax_analize.c \
	src/init/parse_cmd.c \
	src/setup_exec/open_files.c \
	src/setup_exec/setup_heredoc.c \
	src/setup_exec/expand_heredoc.c \
	src/setup_exec/setup_shell.c \
	src/exec/exec_cmd.c \
	src/exec/make_dup.c \
	src/exec/set_dup.c \
	src/exec/manage_heredoc.c \
	src/exec/check_builtins.c \
	src/exec/mini_cd.c \
	src/exec/mini_env_echo_pwd.c \
	src/exec/mini_unset_export.c \
	src/exec/minicd_utils.c \
	src/clean_free/clean_fds.c \
	src/clean_free/free_structs.c \
	src/clean_free/put_errors.c
	# src/others/signals.c

SRCS_BONUS = \
	src/main/main_bonus.c \
	src/init/init_env.c \
	src/init/tokenizer_bonus.c \
	src/init/wildcard_bonus.c \
	src/init/wildcard_utils_bonus.c \
	src/init/parser.c \
	src/init/syntax_analize.c \
	src/init/parse_cmd.c \
	src/setup_exec/open_files.c \
	src/setup_exec/setup_heredoc.c \
	src/setup_exec/expand_heredoc.c \
	src/setup_exec/setup_shell.c \
	src/exec/exec_cmd.c \
	src/exec/make_dup.c \
	src/exec/set_dup.c \
	src/exec/manage_heredoc.c \
	src/exec/check_builtins.c \
	src/exec/mini_cd.c \
	src/exec/mini_env_echo_pwd.c \
	src/exec/mini_unset_export.c \
	src/exec/minicd_utils.c \
	src/clean_free/clean_fds.c \
	src/clean_free/free_structs.c \
	src/clean_free/put_errors.c
	# src/others/signals.c

################################################################################
#                             OBJECTS & DEPS                                   #
################################################################################

OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)
DEPS		= $(OBJS:%.o=$(DEPDIR)/%.d)
DEPS_BONUS	= $(OBJS_BONUS:%.o=$(DEPDIR)/%.d)

LIBFT_A		= $(LIBFT_DIR)/libft.a
HEADERS		= inc/minishell.h libft/libft.h
HEADERS_BONUS	= inc/minishell_bonus.h libft/libft.h

################################################################################
#                              RULES                                           #
################################################################################

all: dir $(LIBFT_A) $(NAME)

bonus: dir $(LIBFT_A) $(NAME_BONUS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS) -o $@
	@echo "\033[32mPLVS VLTRA\033[0m"

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) $(LDFLAGS) -o $@
	@echo "\033[36mPLVS VLTRA BONUS\033[0m"

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT_A):
	@make -C $(LIBFT_DIR) --silent

dir:
	@mkdir -p $(OBJDIR) $(DEPDIR)

clean:
	@make -C $(LIBFT_DIR) clean --silent
	@rm -rf $(OBJDIR) $(DEPDIR)
	@echo "\033[31mNON PLVS VLTRA\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --silent
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re dir bonus
