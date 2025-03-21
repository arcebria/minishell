/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:40 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/19 21:30:08 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_pipes * 2)
	{
		close(shell->pipes[i]);
		i++;
	}
}

void	close_fds(t_command *cmd, t_shell *shell)
{
	t_command		*c_tmp;
	t_redirection	*r_tmp;

	c_tmp = cmd;
	while (c_tmp)
	{
		r_tmp = c_tmp->redirs;
		while (r_tmp)
		{
			if (r_tmp->fd_in == -1)
				close(r_tmp->fd_in);
			if (r_tmp->fd_out == -1)
				close(r_tmp->fd_out);
			r_tmp = r_tmp->next;
		}
		c_tmp = c_tmp->next;
	}
	close_pipes(shell);
}

int	cmd_size(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	redir_one_cmd(t_redirection *redir)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
				return (1);
			close(tmp->fd_in);
		}
		else if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
				return (1);
			close(tmp->fd_out);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir_pipes(t_redirection *redir, t_shell *shell)
{
	if (shell->child == 0)
	{
		if (!redir)
		{
			if (dup2(shell->pipes[1], STDOUT_FILENO) == -1)
				return (1);
		}
		else
		{
			if (redir_first_child(redir, shell))
				return (1);
		}
	}
	else if (shell->child == shell->n_pipes)
	{
		if (!redir)
		{
			if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == - 1)
				return (1);
		}
		else
		{
			if (redir_last_child(redir, shell))
				return (1);
		}
	}
	else
	{
		if (!redir)
		{
			if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
				return (1);
			if (dup2(shell->pipes[2 * shell->child + 1], STDOUT_FILENO) == -1)
				return (1);	
		}
		else
		{
			if (redir_n_child(redir, shell))
				return (1);
		}
	}
	return (0);
}

int	dup_files(t_redirection *redir, t_shell *shell)
{
	if (shell->n_cmds == 1)
	{
		if (redir_one_cmd(redir) == 1)
			return (1);
	}
	else if (shell->n_cmds > 1)
	{
		if (redir_pipes(redir, shell) == 1)
			return (1);
	}
	return (0);
}

void	exe_child(t_command *cmd, t_shell *shell)
{
	if (dup_files(cmd->redirs, shell) == 1)
		exit(1);
	close_pipes(shell);
	execve(cmd->path, cmd->args, cmd->env_array);
	perror("command");
	exit(127);
}

void 	clean_fds(t_command *cmd)
{
	t_command		*c_tmp;
	t_redirection	*r_tmp;

	c_tmp = cmd;
	while (c_tmp)
	{
		r_tmp = c_tmp->redirs;
		while (r_tmp)
		{
			if (r_tmp->type == REDIR_IN)
				close(r_tmp->fd_in);
			if (r_tmp->type == REDIR_OUT || r_tmp->type == APPEND)
				close(r_tmp->fd_out);
			r_tmp = r_tmp->next;
		}
		c_tmp = c_tmp->next;
	}
}

int	exe_parent(t_command *cmd, t_shell *shell)
{
	int		exit_status;
	int		status;
	pid_t	wpid;

	exit_status = 1;
	shell->child--;
	close_fds(cmd, shell);
	clean_fds(cmd);
	while (shell->child >= 0)
	{
		wpid = waitpid(shell->pids[shell->child], &status, 0);
		if (wpid == shell->pids[shell->n_pipes])
		{
			if (shell->child == (shell->n_pipes) && WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		shell->child--;
	}
	free(shell->pipes);
	free(shell->pids);
	return (exit_status);
}

int	exec_cmd(t_command *cmd, t_shell *shell, t_env *env)
{
	t_command	*c_tmp;

	if (!cmd || !cmd->args)
		return (1);
	c_tmp = cmd;
	while (shell->child < shell->n_cmds)
	{
		get_cmd(c_tmp, env);
		shell->pids[shell->child] = fork();
		if (shell->pids[shell->child] == -1)
			return (perror("fork"), 1);
		else if (shell->pids[shell->child] == 0)
			exe_child(c_tmp, shell);
		shell->child++;
		c_tmp = c_tmp->next;
	}
	return (exe_parent(cmd, shell));
}
