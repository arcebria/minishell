/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:12:52 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/06 17:41:58 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		return ;
	}
	ft_printf("%s\n", dir);
}

//////////////////////////////////////////////////////////////////////////////

void	cd_home(char *home)
{
	home = getenv("HOME");
	if (home)
	{
		if (home)
		{
			if (chdir(home) != 0)
				perror("cd");
		}
		else
			ft_putstr_fd("cd: HOME not set\n", 2);
	}
}

void	cd_oldpwd(char *oldpwd)
{
	if (oldpwd)
	{
		ft_printf("~%s\n", oldpwd);
		if (chdir(oldpwd) != 0)
			perror("cd");
	}
	else
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
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

void	cd(char **args, t_env *env_lst)
{
	char	*home;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_oldpwd(env_lst);
	newpwd = getcwd(NULL, 0);
	home = getenv("HOME");
	if (!args[1])
		cd_home(home);
	else if (ft_strcmp(args[1], "-") == 0)
		cd_oldpwd(oldpwd);
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	update_env(env_lst, "OLDPWD", newpwd);
}

//////////////////////////////////////////////////////////////////////////////

void	echo(char **args)
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
}
