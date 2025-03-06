/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/05 19:23:27 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_loop(t_env *env_lst)
{
	char	input[BUFFER_SIZE];
	char	**args;

	while (1)
	{
		ft_printf("minishell> ");
		if (read(0, input, BUFFER_SIZE) <= 0)
		{
			write(1, "\n", 1);
			break ;
		}
		input[ft_strcspn(input, "\n")] = '\0';
		args = ft_split(input, ' ');
		if (ft_strcmp(args[0], "pwd") == 0)
			pwd();
		if (ft_strcmp(args[0], "cd") == 0)
			cd(args, env_lst);
		if (ft_strcmp(args[0], "echo") == 0)
			echo(args);
		if (ft_strcmp(input, "exit") == 0)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_lst;

	(void)ac;
	(void)av;
	env_lst = init_env(env);
	minishell_loop(env_lst);
	return (0);
}
