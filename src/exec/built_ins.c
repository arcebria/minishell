/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:02:15 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/28 21:53:43 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	mini_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		return ;
	}
	ft_printf("%s\n", dir);
	free(dir);
	exit (0);
}

int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) != 0)
			return (perror("cd"), 1);
	}
	else
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	return (0);
}

int	cd_oldpwd(char *oldpwd)
{
	if (oldpwd)
	{
		ft_printf("~%s\n", oldpwd);
		if (chdir(oldpwd) != 0)
			return (perror("cd"), 1);
	}
	else
		return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
	return (0);
}

void	update_env(t_env *env_lst, char *key, char *new_value)
{
	t_env	*tmp;

	if (!env_lst || !key || !new_value)
		return ;
	tmp = env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_oldpwd(t_env *env)
{
	char	*pwd;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
			return (pwd = tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	cd_path(char *path)
{
	char	*test_cwd;

	if (chdir(path) != 0)
		return (perror("cd"), 1);
	else
	{
		test_cwd = getcwd(NULL, 0);
		if (!test_cwd)
		{
			err_out("cd: error retrieving current directory: ",
				"getcwd: cannot access parent directories: ",
				strerror(errno), "");
			return (cd_home());
		}
		free(test_cwd);
	}
	return (0);
}

int	mini_cd(char **args, t_env *env_lst, int n_cmds)
{
	char	*oldpwd;
	char	*newpwd;
	int		exit_status;

	exit_status = 0;
	if (n_cmds > 1)
		return (0);
	oldpwd = get_oldpwd(env_lst);
	newpwd = getcwd(NULL, 0);
	if (!args[1])
		exit_status = cd_home();
	else if (ft_strcmp(args[1], "-") == 0)
		exit_status = cd_oldpwd(oldpwd);
	else
		exit_status = cd_path(args[1]);
	return (update_env(env_lst, "OLDPWD", newpwd), free(newpwd), exit_status);
}

void	mini_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (!ft_strncmp(args[i], "-n", 2))
	{
		if (ft_strspn(args[i], "-n") == ft_strlen(args[i]))
		{
			new_line = 0;
			i++;
		}
		else
			break ;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	exit (0);
}

void	check_built_ins(t_command *cmd, t_env *env)
{
	(void)env;
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(cmd->args[0], "echo"))
		mini_echo(cmd->args);
	//else if (ft_strcmp(cmd->args[0], "env"))
	//	mini_env(env);
	//else if (ft_strcmp(cmd->args[0], "export"))
	//	mini_export(env);
	//else if (ft_strcmp(cmd->args[0], "unset"))
	//	mini_unset(env);
}
