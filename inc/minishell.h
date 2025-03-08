/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:58 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/08 19:42:32 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

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
	t_redirection		*redirs;
	struct s_command	*next;
	int					background;
}	t_command;

/*typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;*/

t_token	*tokenizer(char *input);
void	free_tokens(t_token **token);
//void	echo(char **args);
//void	cd(char **args, t_env *env_lst);
//void	pwd(void);
//t_env	*init_env(char **env);

#endif
