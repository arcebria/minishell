/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:44 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/11 17:25:26 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell_bonus.h"

int	check_initial_segment(const char *p, const char *filename, int *seg_len)
{
	if (*p != '*')
	{
		while (p[*seg_len] && p[*seg_len] != '*')
			*seg_len += 1;
		if (ft_strncmp(filename, p, *seg_len) != 0)
			return (1);
	}
	return (0);
}

int	process_segment(const char **pos, const char **p, int seg_len, int n)
{
	int     found;

	found = 0;
	while (**pos && ((*p - *pos) < n))
	{
		if (ft_strncmp(*pos, *p, seg_len) == 0)
		{
			found = 1;
			break ;
		}
		(*pos)++;
	}
	return (found);
}

int	handle_pattern_segments(const char *pattern, const char *filename, int n)
{
	const char  *p;
	const char  *pos;
	int         seg_len;

	p = pattern;
	pos = filename;
	while ((p - pattern) < n && *p)
	{
		while ((p - pattern) < n && *p == '*')
			p++;
		seg_len = 0;
		while ((p - pattern) + seg_len < n && p[seg_len] && p[seg_len] != '*')
			seg_len++;
		if (seg_len == 0)
			break ;
		if (!process_segment(&pos, &p, seg_len, n))
			return (1);
		p += seg_len;
		pos += seg_len;
	}
	return (0);
}
