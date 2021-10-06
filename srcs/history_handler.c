#include "../inc/minishell.h"

void	ft_add_history(t_mother *s)
{
	if (s->line != NULL)
		add_history(s->line);
}

void	ft_clear_history()
{
	clear_history();
	printf("clear_history() activated\n");
}
