/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:58 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/17 16:15:13 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
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
	AMPERSAND, // &
}	t_token_type;

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
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				**env_array;
	char				*path;
	t_redirection		*redirs;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_token		*tokenizer(char *input);
void		free_tokens(t_token **token);
t_command	*parse_pipeline(t_token	*token);
int			syntax_analize(t_token *tokens);
void		free_commands(t_command	**cmds);
void		free_redir(t_redirection **redir);
void		get_cmd(t_command *cmd, t_env *env);
//void	echo(char **args);
//void	cd(char **args, t_env *env_lst);
//void	pwd(void);
t_env		*init_env(char **env);
int			exec_cmd(t_command *cmd, t_env *env);

#endif
