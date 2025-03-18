/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:40 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/18 20:53:14 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	dup_files(t_redirection *redir, int size)
{
	t_redirection	*tmp;

	tmp = redir;
	if (size == 1)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_IN)
			{
				if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
					return (1);
				close(tmp->fd_in);
				ft_putendl_fd("fd_in redireccionado", 1);
			}
			else if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			{
				if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
					return (1);
				close(tmp->fd_out);
				ft_putendl_fd("fd_out redireccionado", 0);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

void	exe_child(t_command *cmd, int size)
{
	if (cmd->redirs)
		dup_files(cmd->redirs, size);
	execve(cmd->path, cmd->args, cmd->env_array);
	perror("command");
	exit (127);
}

int	exe_parent(t_command *cmd, pid_t child)
{
	int		exit_status;
	int		status;
	pid_t	wpid;

	(void)cmd;
	exit_status = 1;
	/*if (cmd->redirs)
	{
		close(cmd->redirs->fd_in);
		close(cmd->redirs->fd_out);
	}*/
	wpid = waitpid(child, &status, 0);
	if (wpid == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

int	exec_cmd(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		size;

	if (!cmd || !cmd->args)
		return (0);
	size = cmd_size(cmd);
	get_cmd(cmd, env);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		exe_child(cmd, size);
	return (exe_parent(cmd, pid));
}
