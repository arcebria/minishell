/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:21:33 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/15 15:34:51 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell_bonus.h"

static int	ft_strncmp_wildcard(const char *filename, const char *pattern,
		int n)
{
	int	initial_check;
	int	seg_len;

	seg_len = 0;
	initial_check = check_initial_segment(pattern, filename, &seg_len);
	if (initial_check)
		return (1);
	return (handle_pattern_segments(pattern + seg_len, filename + seg_len, n));
}

char	*expand_wildcard(int start, int end, char *pattern)
{
	char	**files;
	char	*result;
	size_t	total_len;
	int		pattern_len;
	int		i;

	files = get_dir_elements();
	result = NULL;
	total_len = 0;
	pattern_len = end - start;
	i = 0;
	while (files && files[i])
	{
		if (ft_strncmp_wildcard(files[i], pattern, pattern_len) == 0)
			total_len += ft_strlen(files[i]) + 1;
		i++;
	}
	if (total_len == 0)
		return (NULL);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (files && files[i])
	{
		if (ft_strncmp_wildcard(files[i], pattern, pattern_len) == 0)
		{
			ft_strcat(result, files[i]);
			ft_strcat(result, " ");
		}
		i++;
	}
	ft_free_array(files);
	return (result);
}

char	*fuse_results(char *new_input, int start, int *end, char *expanded)
{
	char	*before;
	char	*after;
	char	*tmp;
	char	*result;
	int		expanded_len;

	before = ft_strndup(new_input, start);
	after = ft_strdup(new_input + *end);
	tmp = ft_strjoin(before, expanded);
	if (!tmp)
		return (free(before), free(after), NULL);
	free(before);
	result = ft_strjoin(tmp, after);
	if (!result)
		return (free(after), NULL);
	free(tmp);
	free(after);
	expanded_len = ft_strlen(expanded);
	*end = start + expanded_len;
	return (result);
}
