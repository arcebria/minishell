/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/15 22:27:14 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_loop(t_env *env)
{
	char		*input;
	t_token		*token;
	t_command	*command;

	command = NULL;
	while (1)
	{
		input = readline("\033[1;34mminishell>\033[0m ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		token = tokenizer(input);
		if (syntax_analize(token) == 0)
			command = parse_pipeline(token);
		get_cmd(command, env);
		if (ft_strcmp(input, "exit") == 0)
		{
			free_tokens(&token);
			free(input);
			break ;
		}
		free_tokens(&token);
		free_commands(&command);
		free(input);
	}
	rl_clear_history();
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
