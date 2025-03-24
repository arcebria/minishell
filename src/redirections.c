//header

//problemas cuando se redirecciona a dos outputs diferentes ls > out > out2

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
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND))
		{
			if (set_output_redir(tmp, tmp->fd_out, 0))
				return (1);
		}
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
	t_redirection	*last_out;

	last_out = NULL;
	tmp = redir;
	while (tmp)
	{
		tmp->flag_in = 0;
		if (tmp->type == REDIR_IN && set_input_redir(tmp, tmp->fd_in, 1))
			return (1);
		else if (tmp->type != REDIR_IN && tmp->flag_in == 0)
		{	
			if (set_input_redir(tmp, shell->pipes[2 * shell->child - 2], 1))
				return (1);
		}
		if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			last_out = tmp;
		tmp = tmp->next;
	}
	if (last_out && set_output_redir(last_out, last_out->fd_out, 0))
		return (1);
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