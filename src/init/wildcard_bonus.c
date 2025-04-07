/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:21:33 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/07 15:22:04 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_token_type(t_token_type type)
{
	switch (type)
	{
		case WORD:
			printf("token->type: WORD\n");
			break;
		case PIPE:
			printf("token->type: PIPE\n");
			break;
		case REDIR_IN:
			printf("token->type: REDIR_IN\n");
			break;
		case REDIR_OUT:
			printf("token->type: REDIR_OUT\n");
			break;
		case HEREDOC:
			printf("token->type: HEREDOC\n");
			break;
		case APPEND:
			printf("token->type: APPEND\n");
			break;
		default:
			printf("token->type: UNKNOWN\n");
			break;
	}
}

static void	print_token(t_token *token)
{
	if (!token)
		return;
	printf("Value: %s\n", token->value);
	print_token_type(token->type);
}

char     *expand_wildcard_input(t_token **token, char *input, int i)
{
    printf("input[%d] = %s\n", i, input);
    printf("toke->value: %s\n", (*token)->value);
	print_token_type((*token)->type);

    return (token);
}