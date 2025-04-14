#include "../inc/minishell.h"

int	is_in_single_quote(const char *str, int pos)
{
	int		in_single;
	int		in_double;
	int		i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (i < pos)
	{
		if (str[i] == '"' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\'' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single);
}
