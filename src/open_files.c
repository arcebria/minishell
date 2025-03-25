/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:18:35 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/25 21:41:20 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_heredoc(t_redirection *redir, t_shell *shell)
{
	int		tmp_fd;
	char	*line;
	char	*delimiter;

	shell->here_doc = 1;
	delimiter = redir->file;
	tmp_fd = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd == -1)
		err_out("minishell: heredoc: ", strerror(errno), NULL, NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putstr_fd(line, tmp_fd);
		ft_putstr_fd("\n", tmp_fd);
		free(line);
	}
	close(tmp_fd);
	redir->fd_in = open("/tmp/heredoc.tmp", O_RDONLY);
	if (redir->fd_in == -1)
		err_out("minishell: heredoc: ", strerror(errno), NULL, NULL);
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

t_shell	*setup_exec(t_command *cmd)
{
	t_shell			*shell;
	t_command		*c_tmp;
	t_redirection	*r_tmp;

	shell = init_shell(cmd);
	c_tmp = cmd;
	while (c_tmp)
	{
		r_tmp = c_tmp->redirs;
		while (r_tmp)
		{
			if (r_tmp->type == REDIR_IN)
				open_infile(r_tmp);
			else if (r_tmp->type == HEREDOC)
				open_heredoc(r_tmp, shell);
			else if (r_tmp->type == REDIR_OUT)
				open_outfile(r_tmp, 0);
			else if (r_tmp->type == APPEND)
				open_outfile(r_tmp, 1);
			r_tmp = r_tmp->next;
		}
		c_tmp = c_tmp->next;
	}
	create_pipes(shell);
	return (shell);
}
