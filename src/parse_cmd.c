/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:09:03 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/15 22:37:03 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	int		size;
	int		i;
	char	**array;
	char	*env_var;
	t_env	*tmp;

	tmp = env;
	size = env_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (tmp)
	{
		env_var = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		if(!env_var)
			return (NULL);
		/*no funciona por una posible mala implementacion de estas funciones
		mirar de implementar stcpy y strcat*/
		ft_strlcpy(env_var, tmp->key, ft_strlen(tmp->key));
		ft_strlcat(env_var, "=", 1);
		ft_strlcat(env_var, tmp->value, ft_strlen(tmp->value));
		array[i++] = env_var;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

void	get_cmd(t_command *cmd, t_env *env)
{
	char	**env_array;

	(void)cmd;
	env_array = env_to_array(env);
	/*if (ft_strchr(cmd->cmd, '/'))
		cmd->path = ft_strdup(cmd->cmd);
	else
		cmd->path = get_path()*/
	int i = 0;
	while (env_array[i])
		printf("%s\n", env_array[i++]);
}
