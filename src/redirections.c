//header

#include "../inc/minishell.h"

int	set_input_redir(t_redirection *redir, int fd, int type)
{
	if (type == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
		if (redir->next)
			redir->next->flag_in = 1;
	}
	return (0);
}

int	set_output_redir(t_redirection *redir , int fd, int type)
{
	if (type == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
		close(fd);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
		close(fd);
		if (redir->next)
			redir->next->flag_out = 1;
	}
	return (0);
}


int redir_first_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN && set_input_redir(tmp, tmp->fd_in, 0))
			return (1);
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND) 
				&& set_output_redir(tmp, tmp->fd_out, 0))
			return (1);
		else
		{
			if (set_output_redir(tmp, shell->pipes[1], 0))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir_last_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		tmp->flag_in = 0;
		if (tmp->type == REDIR_IN && set_input_redir(tmp, tmp->fd_in, 1))
			return (1);
		else if (tmp->type != REDIR_IN && tmp->flag_in == 0 
				&& set_input_redir(tmp, shell->pipes[2 * shell->child - 2], 1))
			return (1);
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND) 
				&& set_output_redir(tmp, tmp->fd_out, 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);	
}

int	redir_n_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		tmp->flag_in = 0;
		tmp->flag_out = 0;
		if (tmp->type == REDIR_IN && set_input_redir(tmp, tmp->fd_in, 1))
			return (1);
		else if (tmp->type != REDIR_IN && tmp->flag_in == 0 
				&& set_input_redir(tmp, shell->pipes[2 * shell->child - 2], 0))
			return (1);
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND) 
				&& set_output_redir(tmp, tmp->fd_out, 1))
			return (1);
		else if (tmp->type != REDIR_OUT && tmp->type != APPEND && tmp->flag_out == 0 
				&& set_output_redir(tmp, shell->pipes[2 * shell->child + 1], 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}















































/*int	redir_pipes(t_redirection *redir, t_shell *shell)
{
	t_redirection *tmp;

	tmp = redir;
	if (shell->child == 0)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_IN)
			{
				if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
					return (1);
				close(tmp->fd_in);
				printf("Primer nodo -- File: %s fd_in: %d\n", tmp->file, tmp->fd_in);
			}
			if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			{
				printf("Primer nodo -- File: %s fd_out: %d\n", tmp->file, tmp->fd_out);
				if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
					return (1);
				close(tmp->fd_out);
			}
			else
			{
				printf("CACA -- File: %s fd_out: %d\n", tmp->file, tmp->fd_out);
				if (dup2(shell->pipes[1], STDOUT_FILENO) == -1)
					return (1);
			}
			tmp = tmp->next;
		}
	}
	else if (shell->child == shell->n_pipes)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_IN)
			{
				printf("Segundo nodo -- File: %s fd_in: %d\n", tmp->file, tmp->fd_in);
				if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
					return (1);
				close(tmp->fd_in);
			}
			else
			{
				if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
					return (1);
			}
			if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			{
				printf("Segundo nodo -- File: %s fd_out: %d\n", tmp->file, tmp->fd_out);
				if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
					return (1);
				close (tmp->fd_out);
			}
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (tmp->type == REDIR_IN)
			{
				if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
					return (1);
				close (tmp->fd_in);
			}
			else
			{
				if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
					return (1);
			}
			if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			{
				if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
					return (1);
				close (tmp->fd_out);
			}
			else
			{
				if (dup2(shell->pipes[2 * shell->child + 1], STDOUT_FILENO) == -1)
					return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}*/