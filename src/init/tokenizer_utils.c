/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:31:39 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/11 21:35:02 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_quotes(t_token **token, char *input, int *i)
{
	if (input[*i] == '"' || input[*i] == '\'')
	{
		if (extract_quoted_token(token, input, i))
			return (1);
	}
	return (0);
}

int	handle_operator_token(t_token **token, char *input, int *i)
{
	if (handle_redirection(token, input, i))
		return (1);
	return (0);
}

int	handle_redirection(t_token **token, char *input, int *i)
{
	if (input[*i] != '<' && input[*i] != '>')
		return (0);
	if (input[*i + 1] == input[*i])
	{
		if (input[*i] == '<')
			add_token(token, "<<", HEREDOC);
		else
			add_token(token, ">>", APPEND);
		*i += 2;
	}
	else
	{
		if (input[*i] == '<')
			add_token(token, "<", REDIR_IN);
		else
			add_token(token, ">", REDIR_OUT);
		(*i)++;
	}
	return (1);
}
