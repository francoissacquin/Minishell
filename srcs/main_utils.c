#include "../inc/minishell.h"

int	ft_lexer_handler(t_mother *s)
{
	int		parse_ret;
	pid_t	*pid;

	parse_ret = 0;
	pid = ft_return_global_pid();
	minilexer(s);
	assign_types(s);
	redir_input_handler(s);
	parse_ret = miniparser(s);
	if (parse_ret == 1)
		*pid = 0;
	return (parse_ret);
}

int	ft_weird_readline(t_mother *s)
{
	free_t_loop(s);
	free(s->line);
	s->ret = 0;
	return (s->ret);
}

void	ft_control_d(t_mother *s)
{
	free_t_loop(s);
	free_t_mother(s);
	write(1, "exit\n", 5);
	exit(s->ret);
}

void	exec_and_repeat(t_mother *s)
{
	pid_t	*pid;

	pid = ft_return_global_pid();
	multicommands(s);
	*pid = 0;
	free_t_loop(s);
	free(s->line);
}

int	ft_input_is_spaces(char *str)
{
	int		i;
	int		len;
	char	*temp;

	len = ft_strlen(str);
	if (len < 1)
		return (0);
	temp = ft_malloc(&temp, (len + 1) * sizeof(char));
	i = 0;
	while (i < len)
	{
		temp[i] = ' ';
		i++;
	}
	temp[i] = '\0';
	i = ft_strcmp(temp, str);
	free(temp);
	if (i == 0)
		return (1);
	else
		return (0);
}
