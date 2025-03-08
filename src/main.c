/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/08 22:05:06 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_loop()
{
	char		*input;
	t_token		*token;
	t_command	*command;

	(void)command;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		token = tokenizer(input);

		if (ft_strcmp(input, "exit") == 0)
		{
			free_tokens(&token);
			free(input);
			break ;
		}
		//if (token)
		free_tokens(&token);
		free(input);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	//t_env	*env_lst;

	(void)ac;
	(void)av;
	(void)env;
	//t_token *token = NULL;
	//(void)env_lst;
	//env_lst = init_env(env);
	minishell_loop();
	return (0);
}
