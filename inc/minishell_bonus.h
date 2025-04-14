/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:58 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/11 17:25:40 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

# define S_E_PIPE "minishell: syntax error near unexpected token `|'\n"
# define S_E_REDIR "minishell: syntax error near unexpected token `newline'\n"

typedef enum s_token_type
{
	WORD, // TEXTO
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // <<
	APPEND, // >>
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

//		Wildcard
void		ft_free_array(char **arr);
char		**get_dir_elements(void);
char		*fuse_results(char *new_input, int start, int *end, char *expanded);
int		check_initial_segment(const char *p, const char *filename, int *seg_len);
int		process_segment(const char **pos, const char **p, int seg_len, int n);
int		handle_pattern_segments(const char *pattern, const char *filename, int n);
char		*expand_wildcard(int start, int end, char *pattern);
char		*manage_wildcard(char *input);

//tokenizer, syntax check and parsing

t_token		*tokenizer(char *input);
int			syntax_analize(t_token *tokens);
t_command	*parse_pipeline(t_token	*token);
t_env		*init_env(char **env);

//set_executor

t_shell		*setup_exec(t_command *cmd, int exit_status, t_env *env);
t_shell		*init_shell(t_command *cmd);
void		create_pipes(t_shell *shell);
void		open_heredoc(t_redirection *redir, t_shell *shell,
				int exit_status, t_env *env);
char		*line_expanded(char *line, t_env *env, int exit_status);

//exec

void		get_cmd(t_command *cmd, t_env *env);
int			exec_cmd(t_command *cmd, t_shell *shell, t_env *env);
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

//manage fds

void		close_fds(t_command *cmd, t_shell *shell);
void		close_pipes(t_shell *shell);

//free structs

void		free_tokens(t_token **token);
void		free_commands(t_command	**cmds);
void		free_tokens(t_token **token);
void		free_env(t_env **env);

//put errors in stderr

void		err_out(char *str1, char *str2, char *str3, char *str4);

#endif
