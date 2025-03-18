/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:18:35 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/18 17:44:45 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_infile(t_command *cmd)
{
	cmd->redirs->fd_in = open(cmd->redirs->file, O_RDONLY, 664);
	if (cmd->redirs->fd_in == -1)
		strerror(errno);
	printf("infile abierto correctamente\n");
}

void	open_outfile(t_command *cmd, int append)
{
	if (append == 0)
		cmd->redirs->fd_out = open(cmd->redirs->file, O_CREAT
				| O_WRONLY | O_TRUNC, 0664);
	else if (append == 1)
		cmd->redirs->fd_out = open(cmd->redirs->file, O_CREAT
				| O_WRONLY | O_APPEND, 0664);
	if (cmd->redirs->fd_out == -1)
		strerror(errno);
	printf("outfile abierto correctamente\n");
}

void	init_redirections(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redirs->type == REDIR_IN)
			open_infile(tmp);
		else if (tmp->redirs->type == REDIR_OUT)
			open_outfile(tmp, 0);
		else if (tmp->redirs->type == APPEND)
			open_outfile(tmp, 1);
		tmp = tmp->next;
	}
}
