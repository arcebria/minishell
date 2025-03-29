#include "../../inc/minishell.h"

void	remove_node(t_env **lst, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	mini_unset(t_command *cmd, t_env **env, t_env **export, int n_cmds)
{
	int		i;

	if (n_cmds > 1)
		return (0);
	if (!cmd->args[1])
		return(ft_putendl_fd("unset: not enough arguments", 2), 1);
	i = 1;
	while (cmd->args[i])
	{
		remove_node(env, cmd->args[i]);
		remove_node(export, cmd->args[i]);
		i++;
	}
	return (0);
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

int	check_parent_builtins(t_command *cmd, t_shell *shell, t_env **env, t_env **export)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		shell->builtins_exit_status = mini_cd(cmd->args, *env, shell->n_cmds);	
		return (1);
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
	{
		shell->builtins_exit_status = mini_unset(cmd, env, export, shell->n_cmds);	
		return (1);
	}
	/*if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		shell->builtins_exit_status = mini_cd(cmd, env, export);	
		return (1);
	}*/
	return (0);
}