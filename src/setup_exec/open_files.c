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

void	open_infile(t_redirection *redir)
{
	redir->fd_in = open(redir->file, O_RDONLY, 644);
	if (redir->fd_in == -1)
		err_out("minishell: ", redir->file, ": ", strerror(errno));
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

void	check_type(t_redirection *red, t_shell *shell, int cnt, int stat)
{
	if (red->type == REDIR_IN)
		open_infile(red);
	else if (red->type == HEREDOC)
		heredoc(red, shell, cnt, stat);
	else if (red->type == REDIR_OUT)
		open_outfile(red, 0);
	else if (red->type == APPEND)
		open_outfile(red, 1);
}

t_shell	*setup_exec(t_command *cmd, int exit_status)
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
			check_type(r_tmp, shell, hd_count++, exit_status);
			r_tmp = r_tmp->next;
		}
		c_tmp = c_tmp->next;
	}
	create_pipes(shell);
	return (shell);
}
