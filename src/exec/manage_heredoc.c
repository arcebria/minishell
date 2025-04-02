#include "../../inc/minishell.h"

void	make_unlink(t_command *cmd, t_shell *shell)
{
	t_command		*c_tmp;
	t_redirection	*r_tmp;

	if (shell->here_doc)
	{
		c_tmp = cmd;
		while (c_tmp)
		{
			r_tmp = c_tmp->redirs;
			while (r_tmp)
			{
				if (r_tmp->type == HEREDOC)
					unlink(r_tmp->hd_filename);
				r_tmp = r_tmp->next;
			}
			c_tmp = c_tmp->next;
		}
	}
}

int	search_heredoc(t_redirection *redir)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
