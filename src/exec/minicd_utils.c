#include "../../inc/minishell.h"

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
