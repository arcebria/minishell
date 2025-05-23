/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:58 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/14 22:35:51 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

# define S_E_PIPE "minishell: syntax error near unexpected token `|'\n"
# define S_E_REDIR "minishell: syntax error near unexpected token `newline'\n"

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	AMPERSAND,
	OR
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		n_pipes;
	int		n_cmds;
	int		*pipes;
	pid_t	*pids;
	int		child;
	int		flag_in;
	int		flag_out;
	int		here_doc;
	int		hd_count;
	int		builtins_exit_status;
}	t_shell;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	int						type;
	char					*file;
	int						fd_in;
	int						fd_out;
	char					*hd_filename;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	char				**env_array;
	char				*path;
	t_redirection		*redirs;
	struct s_command	*next;
}	t_command;

//loop

int			minishell_loop(t_env *env, t_env *export);

//tokenizer, syntax check and parsing

t_token		*tokenizer(char *input, t_env *env, int exit_status);
int			syntax_analize(t_token *tokens);
t_command	*parse_pipeline(t_token	*token);
t_env		*init_env(char **env);
int			handle_quotes(t_token **token, char *input, int *i, int *flag);
int			handle_operator_token(t_token **token, char *input, int *i);
int			handle_redirection(t_token **token, char *input, int *i);
int			handle_pipe_ampersand(t_token **token, char *input, int *i);
t_token		*find_last(t_token *node);
void		add_token(t_token **token, char *value, t_token_type type);
int			extract_quoted_token(t_token **token, char *input, int *i);
int			extract_word(t_token **token, char *input, int *i);
void		handle_word(t_token **token, char *input, int *i, int *export_mode);

//signals

void		sigint_handler(int signum);
void		setup_signals(int signal);
void		disable_signal_echo(void);

//set_executor

t_shell		*setup_exec(t_command *cmd, int exit_status, t_env *env);
t_shell		*init_shell(t_command *cmd);
void		create_pipes(t_shell *shell);
void		open_heredoc(t_redirection *redir, t_shell *shell,
				int exit_status, t_env *env);
char		*check_to_expand(char *line, int *i, t_env *env, int exit_status);

//exec

void		get_cmd(t_command *cmd, t_env *env);
int			exec_cmd(t_command *cmd, t_shell *shell, t_env **env, t_env **exp);
int			cmd_size(t_command *cmd);
int			set_dup(t_redirection *redir, t_shell *shell);
int			dup_first_child(t_redirection *redir, t_shell *shell);
int			dup_last_child(t_redirection *redir, t_shell *shell);
int			dup_n_child(t_redirection *redir, t_shell *shell);
int			search_heredoc(t_redirection *redir);
void		make_unlink(t_command *cmd, t_shell *shell);

//builtins

void		check_child_builtin(t_command *cmd, t_env **env);
int			check_parent_builtin(t_command *cmd, t_shell *shell, t_env **env,
				t_env **export);
int			mini_cd(char **args, t_env *env_lst, int n_cmds);
void		update_env(t_env *env_lst, char *key, char *new_value);
char		*get_oldpwd(t_env *env);
int			mini_pwd(void);
int			mini_echo(char **args);
int			mini_env(t_env *env_lst);
int			mini_unset(t_command *cmd, t_env **env, t_env **export, int n_cmds);
int			mini_export(t_command *cmd, t_env *export, int flag);
char		*export_key(char *s, int len);
int			find_key(char *args);
void		ft_bubble(t_env *export);
void		ft_swap_lst(t_env *a, t_env *b);
int			should_skip_creation(char *arg, int value_start, int flag);
char		*get_export_value(char *arg, int value_start);
t_env		*init_new_node(char *arg, int value_start, char *temp_value);
void		append_to_list(t_env *export, t_env *new_node);

//expansor && env

t_env		*init_no_env(int flag);
void		ft_env(t_env *env_lst);
t_command	*init_command(void);
void		add_redir_utils(t_redirection *tmp,
				t_command *cmd, t_redirection *redir);
void		ft_expansor(t_token *token, t_env *env, int exit_status);

//manage fds

void		close_fds(t_command *cmd, t_shell *shell);
void		close_pipes(t_shell *shell);

//free structs

void		free_tokens(t_token **token);
void		free_commands(t_command	**cmds);
void		free_env(t_env **env);

//put errors in stderr

void		err_out(char *str1, char *str2, char *str3, char *str4);

#endif
