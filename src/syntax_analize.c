/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:47:30 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/13 21:29:14 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_first_and_last(t_token *tokens)
{
	t_token	*head;
	t_token	*last;
	t_token	*tmp;

	if (!tokens)
		return (0);
	head = tokens;
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	last = tmp;
	if (head->value[0] == '|' || last->value[0] == '|')
	{
		ft_putstr_fd(S_E_PIPE, 2);
		return (1);
	}
	return (0);
}

int	check_consecutives(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->next && ft_isspecial(tmp->value[0])
			&& ft_isspecial(tmp->next->value[0]))
		{
			ft_putstr_fd(S_E_PIPE, 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_file(t_token	*tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if ((tmp->value[0] == '<' || tmp->value[0] == '>')
			&& !tmp->next)
		{
			ft_putstr_fd(S_E_REDIR, 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	syntax_analize(t_token *tokens)
{
	int	flag;
	int	sec_flag;

	flag = check_first_and_last(tokens);
	if (flag == 0)
	{
		flag = check_consecutives(tokens);
		sec_flag = check_file(tokens);
	}
	if (flag || sec_flag)
		return (1);
	return (0);
}
