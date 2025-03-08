/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:36:51 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/08 17:46:44 by arcebria         ###   ########.fr       */
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
