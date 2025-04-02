//header

#include "../../inc/minishell.h"

void	err_out(char *str1, char *str2, char *str3, char *str4)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putstr_fd(str3, STDERR_FILENO);
	ft_putendl_fd(str4, STDERR_FILENO);
}
