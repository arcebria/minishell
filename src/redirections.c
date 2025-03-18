/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:18:35 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/18 20:43:57 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_infile(t_redirection *redir)
{
	redir->fd_in = open(redir->file, O_RDONLY, 664);
	if (redir->fd_in == -1)
		strerror(errno);
	printf("infile abierto correctamente\n");
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
	printf("outfile abierto correctamente\n");
}

void	init_redirections(t_command *cmd)
{
	t_redirection	*tmp;

	if (!cmd->redirs)
		return ;
	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			open_infile(tmp);
		else if (tmp->type == REDIR_OUT)
			open_outfile(tmp, 0);
		else if (tmp->type == APPEND)
			open_outfile(tmp, 1);
		tmp = tmp->next;
	}
}
