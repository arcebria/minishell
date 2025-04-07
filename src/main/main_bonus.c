/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 16:40:35 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell_bonus.h"

void	minishell_loop(t_env *env)
{
	char		*input;
	t_token		*token;
	t_command	*command;
	t_shell		*shell;
	int	exit_status;

	exit_status = 0;
	command = NULL;
	while (1)
	{
		input = readline("\033[1;34mminishell_bonus>\033[0m ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		token = tokenizer(input);
		if (syntax_analize(token) == 0)
		{
			command = parse_pipeline(token);
			shell = setup_exec(command, exit_status, env);
			exit_status = exec_cmd(command, shell, env);
		}
		else
		{
			free(input);
			free_tokens(&token);
			continue ;
		}
		//(void)exit_status;
		printf("%d\n", exit_status);
		if (ft_strcmp(input, "exit") == 0)
		{
			free_tokens(&token);
			free_commands(&command);
			free_env(&env);
			free(shell);
			free(input);
			break ;
		}
		free_tokens(&token);
		free_commands(&command);
		free(shell);
		free(input);
	}
	free_env(&env);
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
