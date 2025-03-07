/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/07 20:14:15 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*last_node;
	size_t		equal_pos;
	int		i;

	head = NULL;
	last_node = NULL;
	i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		equal_pos = ft_strcspn(env[i], "=");
		if (equal_pos == ft_strlen(env[i])) //si no encuentra un = se lo salta y pasa al siguiente str
			continue ;
		new_node->key = ft_substr(env[i], 0, equal_pos);
		new_node->value = ft_strdup(env[i] + equal_pos + 1);
		new_node->next = NULL;
		if (!head)
			head = new_node;

		else
		{
			last_node->next = new_node;
		}
		last_node = new_node;
		i++;
	}
	return (head);
}*/
