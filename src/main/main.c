/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/11 21:14:03 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_lst;
	t_env	*exprt_lst;

	(void)ac;
	(void)av;
	if (!env | !*env)
	{
		env_lst = init_no_env(0);
		exprt_lst = init_no_env(1);
	}
	else
	{
		env_lst = init_env(env);
		exprt_lst = init_env(env);
	}
	minishell_loop(env_lst, exprt_lst);
	return (0);
}
