#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../libft/libft.h"

#define BUFFER_SIZE 1024

void	minishell_loop(void)
{
	char	input[BUFFER_SIZE];

	while (1)
	{
		write(1, "minishell> ", 11);
		if (read(0, input, BUFFER_SIZE) <= 0)
		{
			write(1, "\n", 1);
			break ;
		}
		input[ft_strcspn(input, "\n")] = '\0';
		if (ft_strcmp(input, "exit") == 0)
			break ;
		printf("Comando recibido: %s\n", input);
	}
}

int	main(void)
{
	minishell_loop();
	return (0);
}
