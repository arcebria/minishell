#include "../../inc/minishell.h"

int	handle_input(char **input, t_command **command, t_env **env)
{
	*input = readline("\033[1;34mminishell>\033[0m ");
	if (!*input)
		return (0);
	if ((*input)[0])
		add_history(*input);
	else
	{
		free(*input);
		return (1);
	}
	if (ft_strcmp(*input, "exit") == 0)
	{
		free_commands(command);
		free_env(env);
		free(*input);
		return (0);
	}
	return (2);
}

int	process_token(char *input, t_env *env,
			int *exit_status, t_token **token)
{
	*token = tokenizer(input, env, *exit_status);
	if (*token == NULL)
	{
		free(input);
		*exit_status = 1;
		return (1);
	}
	if (syntax_analize(*token) != 0)
	{
		free(input);
		free_tokens(token);
		return (1);
	}
	return (0);
}

void	execute_command(t_token *token, t_env *env,
			t_env *export, int *exit_status)
{
	t_command	*command;
	t_shell		*shell;

	command = parse_pipeline(token);
	shell = setup_exec(command, *exit_status, env);
	*exit_status = exec_cmd(command, shell, env, export);
	setup_signals(1);
	free_tokens(&token);
	free_commands(&command);
	free(shell);
}

void	minishell_loop(t_env *env, t_env *export)
{
	char		*input;
	t_token		*token;
	int			exit_status;
	int			status;

	exit_status = 0;
	setup_signals(1);
	while (1)
	{
		status = handle_input(&input, NULL, &env);
		if (status == 0)
			break ;
		if (status == 1)
			continue ;
		if (process_token(input, env, &exit_status, &token) != 0)
			continue ;
		execute_command(token, env, export, &exit_status);
		free(input);
	}
	free_env(&env);
	rl_clear_history();
	free_env(&export);
}
