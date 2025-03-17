/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:40 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/17 20:53:01 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exe_child(t_command *cmd)
{
	execve(cmd->path, cmd->args, cmd->env_array);
	perror("execve");
	exit (127);
}

int	exe_parent(t_command *cmd, pid_t child)
{
	int		exit_status;
	int		status;
	pid_t	wpid;

	(void)cmd;
	exit_status = 1;
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

	if (!cmd)
		return (0);
	get_cmd(cmd, env);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		exe_child(cmd);
	return (exe_parent(cmd, pid));
}
