/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:57:57 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/08 20:19:09 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**token_to_array(t_token *token)
{
	int		count;
	int		i;
	char	**array;
	t_token	*tmp;

	tmp = token;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	tmp = token;
	i = 0;
	while (i < count)
	{
		array[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	add_args(t_command *cmd, char **token, int *last)
{
	int		count;
	int		i;
	char	**new_args;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_args[count] = ft_strdup(token[*last]);
	new_args[count + 1] = NULL;
	if (cmd->args)
		ft_free_array(cmd->args);
	cmd->args = new_args;
}

t_command	*parse_simple_cmd(t_token *token, char **tokens, int *i)
{
	t_command	*cmd;
	t_token		*tmp;

	tmp = token;
	if (!ft_strcmp(tokens[0], "|"))
		return (NULL);
	cmd = init_command();
	while (tokens[*i] && tmp->type != PIPE)
	{
		if (!ft_strcmp(tokens[*i], "<") || !ft_strcmp(tokens[*i], "<<")
			|| !ft_strcmp(tokens[*i], ">") || !ft_strcmp(tokens[*i], ">>"))
			add_redir(cmd, tokens, i);
		else
			add_args(cmd, tokens, i);
		tmp = tmp->next;
		(*i)++;
	}
	return (cmd);
}

t_command	*build_cmds(char **tokens, t_token *token)
{
	t_command	*new_cmd;
	t_command	*head;
	t_command	*current;
	int			i;

	head = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		new_cmd = parse_simple_cmd(token, tokens, &i);
		if (!new_cmd)
			break ;
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		if (tokens[i] && !ft_strcmp(tokens[i], "|"))
			i++;
	}
	return (head);
}

t_command	*parse_pipeline(t_token	*token)
{
	t_command	*head;
	char		**tokens;

	tokens = token_to_array(token);
	if (!tokens)
		return (NULL);
	head = build_cmds(tokens, token);
	ft_free_array(tokens);
	return (head);
}
