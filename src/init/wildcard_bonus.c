/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:21:33 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/14 16:55:26 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>

#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char  	*manage_new_input(char *new_input, int j, int *i, char *expanded)
{
	char	*old_input;
	char	*result;

	old_input = new_input;
	result = fuse_results(old_input, j, i, expanded);
	free(old_input);
	free(expanded);
	return (result);
}

char	**get_dir_elements(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				count;

	files = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), (NULL));
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			files = ft_realloc(files, count * sizeof(char *),
					(count + 1) * sizeof(char *));
			if (!files)
				return (ft_free_array(files), NULL);
			files[count++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	files = ft_realloc(files, count * sizeof(char *),
			(count + 1) * sizeof(char *));
	files[count] = NULL;
	return (files);
}

char	*manage_wildcard(char *input)
{
	int			i;
	int			j;
	char		*new_input;
	char		*pattern;
	char		*expanded;

	i = 0;
	new_input = ft_strdup(input);
	while (new_input[i])
	{
		if (new_input[i] == '\'')
			while (input[++i] != '\'')
				;
		if (new_input[i] == '"')
			while (input[++i] != '"')
				;
		if (new_input[i] == '*')
		{
			j = i;
			while (j > 0 && new_input[j - 1] != ' ')
				j--;
			while (new_input[i] && new_input[i] != ' ')
				i++;
			pattern = ft_strndup(&new_input[j], i - j);
			expanded = expand_wildcard(j, i, pattern);
			free(pattern);
			if (expanded)
				new_input = manage_new_input(new_input, j, &i, expanded);
		}
		else if (new_input[i])
			i++;
	}
	return (new_input);
}
