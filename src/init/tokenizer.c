/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:54:26 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/14 18:28:52 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_token(t_token **token, char *value, t_token_type type)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->type = type;
	new_node->value = ft_strdup(value);
	if (!*token)
		*token = new_node;
	else
	{
		last_node = find_last(*token);
		last_node->next = new_node;
	}
}

int	extract_quoted_token(t_token **token, char *input, int *i)
{
	char	quote;
	int		start;
	char	*word;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		ft_putstr_fd("Error: Open quotation marks\n", 2);
		return (1);
	}
	word = ft_substr(input, start, *i - start);
	add_token(token, word, WORD);
	free(word);
	(*i)++;
	return (0);
}

t_token	*tokenizer(char *input, t_env *env, int exit_status)
{
	t_token	*token;
	int		i;
	int		export_mode;
	int		flag_quote;

	i = 0;
	flag_quote = 0;
	token = NULL;
	export_mode = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (handle_operator_token(&token, input, &i))
			continue ;
		else if (handle_quotes(&token, input, &i, &flag_quote))
			return (free_tokens(&token), NULL);
		else
			handle_word(&token, input, &i, &export_mode);
	}
	if (!export_mode && !flag_quote)
		ft_expansor(token, env, exit_status);
	return (token);
}
