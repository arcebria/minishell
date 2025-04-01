/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:18:35 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/28 20:53:09 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_and_out(t_redirection *redir)
{
	free(redir->hd_filename);
	err_out("minishell: heredoc: ", strerror(errno), NULL, NULL);
}

char	*get_hd_filename(int hd_count)
{
	char	*num;
	char	*filename;

	num = ft_itoa(hd_count);
	filename = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (filename);
}

char	*search_value(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				return (tmp->value);
			else
				return ("");
		}
		tmp = tmp->next;
	}
	return ("");
}

char	*expand_text(char *line, int *i)
{
	char	*text;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != '$')
		(*i)++;
	text = ft_substr(line, start, *i - start);
	return (text);
}

char	*expand_variable(char *line, int *i, t_env *env)
{
	char	*key;
	char	*value;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '$')
		(*i)++;
	key = ft_substr(line, start, *i - start);
	value = search_value(key, env);
	free(key);
	return (ft_strdup(value));
}

char	*expand_status(int exit_status, int *i)
{
	char	*status;

	status = ft_itoa(exit_status);
	(*i)++;
	return (status);
}

char	*line_expanded(char *line, t_env *env, int exit_status)
{
	char	*result;
	char	*tmp;
	char	*addition;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
				addition = expand_status(exit_status, &i);
			else
				addition = expand_variable(line, &i, env);
		}
		else
			addition = expand_text(line, &i);
		tmp = ft_strjoin(result, addition);
		free(result);
		free(addition);
		result = tmp;
	}
	return (result);
}

/*char	*line_expanded(char *line, t_env *env, int exit_status)
{
	char	*result;
	char	*tmp;
	char	*value;
	int		i = 0, start;
	char	*status;

	result = ft_strdup("");

	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				i++;
				status = ft_itoa(exit_status);
				tmp = ft_strjoin(result, status);
				free(status);
				free(result);
				result = tmp;
				continue ;
			}
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '$')
				i++;
			char *key = ft_substr(line, start, i - start);
			value = search_value(key, env);
			tmp = ft_strjoin(result, value);
			free(result);
			result = tmp;
			free(key);
		}
		else
		{
			start = i;
			while (line[i] && line[i] != '$')
				i++;
			char *normal_text = ft_substr(line, start, i - start);
			tmp = ft_strjoin(result, normal_text);
			free(result);
			result = tmp;
			free(normal_text);
		}
	}
	return (result);
}*/

void	heredoc(t_redirection *redir, t_shell *shell, int count, t_env *env, int stat)
{
	int		tmp_fd;
	char	*line;
	char	*delimiter;

	shell->here_doc = 1;
	delimiter = redir->file;
	redir->hd_filename = get_hd_filename(count);
	tmp_fd = open(redir->hd_filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (tmp_fd == -1)
		free_and_out(redir);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		line = line_expanded(line, env, stat);
		ft_putstr_fd(line, tmp_fd);
		ft_putstr_fd("\n", tmp_fd);
		free(line);
	}
	close(tmp_fd);
	redir->fd_in = open(redir->hd_filename, O_RDONLY);
	if (redir->fd_in == -1)
		free_and_out(redir);
}

void	create_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_pipes * 2)
	{
		if (pipe(shell->pipes + (2 * i)) == -1)
			perror("pipe");
		i++;
	}
}

t_shell	*init_shell(t_command *cmd)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->child = 0;
	shell->n_cmds = cmd_size(cmd);
	shell->n_pipes = shell->n_cmds - 1;
	shell->flag_in = 0;
	shell->flag_out = 0;
	shell->here_doc = 0;
	shell->builtins_exit_status = 1;
	shell->pids = malloc(sizeof(pid_t) * shell->n_cmds);
	if (!shell->pids)
		return (NULL);
	shell->pipes = malloc(sizeof(int *) * shell->n_pipes * 2);
	if (!shell->pipes)
		return (NULL);
	return (shell);
}

void	open_infile(t_redirection *redir)
{
	redir->fd_in = open(redir->file, O_RDONLY, 644);
	if (redir->fd_in == -1)
		err_out("minishell: ", redir->file, ": " , strerror(errno));
}

void	open_outfile(t_redirection *redir, int append)
{
	if (append == 0)
		redir->fd_out = open(redir->file, O_CREAT
				| O_WRONLY | O_TRUNC, 0664);
	else if (append == 1)
		redir->fd_out = open(redir->file, O_CREAT
				| O_WRONLY | O_APPEND, 0664);
	if (redir->fd_out == -1)
		strerror(errno);
}

void	check_type(t_redirection *red, t_shell *shell, int cnt, t_env *env, int stat)
{
	if (red->type == REDIR_IN)
		open_infile(red);
	else if (red->type == HEREDOC)
		heredoc(red, shell, cnt, env, stat);
	else if (red->type == REDIR_OUT)
		open_outfile(red, 0);
	else if (red->type == APPEND)
		open_outfile(red, 1);
}

t_shell	*setup_exec(t_command *cmd, t_env *env, int	exit_status)
{
	t_shell			*shell;
	t_command		*c_tmp;
	t_redirection	*r_tmp;
	int				hd_count;

	hd_count = 0;
	shell = init_shell(cmd);
	c_tmp = cmd;
	while (c_tmp)
	{
		r_tmp = c_tmp->redirs;
		while (r_tmp)
		{
			check_type(r_tmp, shell, hd_count++, env, exit_status);
			r_tmp = r_tmp->next;
		}
		c_tmp = c_tmp->next;
	}
	create_pipes(shell);
	return (shell);
}
