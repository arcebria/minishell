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

#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>

void		ft_free_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char   **get_dir_elements(void)
{
	DIR							*dir;
	struct dirent		*entry;
	char						**files;
	int							count;

	files = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	count = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			files = ft_realloc(files, count * sizeof(char *), (count + 1) * sizeof(char *));
			files[count] = ft_strdup(entry->d_name);
			count++;	
		}
	}
	closedir(dir);
	files = ft_realloc(files, count * sizeof(char *), (count + 1) * sizeof(char *));
	files[count] = NULL;
	return (files);
}

char		*manage_wildcard(char *input)
{
	int			i;
	int			j;
	char		*new_input;
	char		*pattern;
	char		*expanded;

	i = 0;
	new_input = ft_strdup(input);
	while (input[i])
	{
		if (input[i] == '\'') {
			while (input[++i] != '\'')
				;
		}
		if (input[i] == '"') {
			while (input[++i] != '"')
				;
		}
		if (input[i] == '*')
		{ // Encontrar los límites del patrón
			j = i;
			while (input[j] > 0 && input[j - 1] != ' ')
				j--;
			while (input[i] && input[i + 1] != ' ')
				i++;
			pattern = ft_strndup(&new_input[j], i - j);
			expanded = expand_wildcard(j, i, pattern);
			if (expanded)
				new_input = fuse_results(new_input, j, i, expanded, &i);
		}
		else
			i++;
	}
	return (new_input);
}