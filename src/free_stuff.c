/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:36:51 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/17 15:55:23 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tokens(t_token **token)
{
	t_token	*current;
	t_token	*tmp;

	current = *token;
	if (!token || !*token)
		return ;
	while (current)
	{
		tmp = current->next;
		free(current->value);
		free(current);
		current = tmp;
	}
	*token = NULL;
}

void	free_redir(t_redirection **redir)
{
	t_redirection	*current;
	t_redirection	*tmp;

	current = *redir;
	if (!redir || !*redir)
		return ;
	while (current)
	{
		tmp = current->next;
		free(current->file);
		free(current);
		current = tmp;
	}
	*redir = NULL;
}

void	free_commands(t_command	**cmds)
{
	t_command	*current;
	t_command	*tmp;

	current = *cmds;
	if (!cmds || !*cmds)
		return ;
	while (current)
	{
		tmp = current->next;
		free(current->cmd);
		if (current->args)
			ft_free_array(current->args);
		if (current->env_array)
			ft_free_array(current->env_array);
		if (current->path)
			free (current->path);
		if (current->redirs)
			free_redir(&current->redirs);
		free (current);
		current = tmp;
	}
	*cmds = NULL;
}
