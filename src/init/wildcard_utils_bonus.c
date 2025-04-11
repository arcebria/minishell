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

static int	ft_strncmp_wildcard(const char *filename, const char *pattern, int n)
{
	const char	*p;        // puntero que recorre el pattern
	const char	*pos;      // puntero que recorre filename
	int			seg_len;
	int			found;

	p = pattern;
	pos = filename;
	// Si no empieza con '*', el primer segmento debe coincidir desde el inicio
	if (*p != '*')
	{
		seg_len = 0;
		while (p[seg_len] && p[seg_len] != '*')
			seg_len++;
		/* Comparar el primer segmento con el inicio de filename */
		if (ft_strncmp(filename, p, seg_len) != 0)
			return (1);
		/* Avanzamos ambos punteros */
		pos += seg_len;
		p += seg_len;
	}
	while ((p - pattern) < n && *p)
	{
		// Omitir cualquier asterisco consecutivo
		while ((p - pattern) < n && *p == '*')
			p++;
		// Si llegamos al final del patrón, se asume que coincide
		if ((p - pattern) >= n || !*p)
			break ;
		// Calcular longitud del subpattern hasta el próximo asterisco o límite
		seg_len = 0;
		while ((p - pattern) + seg_len < n && p[seg_len] && p[seg_len] != '*')
			seg_len++;
		// Buscar ese subpattern en filename a partir de la posición actual
		found = 0;
		while (*pos)
		{
			if (ft_strncmp(pos, p, seg_len) == 0)
			{
				found = 1;
				break ;
			}
			pos++;
		}
		// Si no se encontró el subpattern, se cancela la búsqueda
		if (!found)
			return (1);
		// Actualizamos el puntero en el pattern y en filename
		p += seg_len;
		pos += seg_len;
	}
	return (0);
}

char	*expand_wildcard(int start, int end, char *pattern) {
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
	while (files[i])
	{
		if (ft_strncmp_wildcard(files[i], pattern, pattern_len) == 0)
			total_len += ft_strlen(files[i]) + 1;
		i++;
	}
	if (total_len == 0)
		return (NULL);
	result = malloc(total_len + 1);
	result[0] = '\0';
	i = 0;
	while (files[i])
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

char *fuse_results(char *new_input, int start, int end, char *expanded, int *new_index)
{
	char	*before;
	char	*after;
	char	*tmp;
	int		expanded_len;

	before = ft_strndup(new_input, start);
	after = ft_strdup(new_input + end);
	expanded_len = ft_strlen(expanded);
	tmp = ft_strjoin(before, expanded);
	free(before);
	free(expanded);
	new_input = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	*new_index = start + expanded_len;
	return (new_input);
}
