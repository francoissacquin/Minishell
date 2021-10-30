#include "../../inc/minishell.h"

void	var_init(t_mother *s)
{
	int	i;

	i = 0;
	s->var = ft_malloc(&s->var, 1 * sizeof(char *));
	s->var[0] = NULL;
}

void	create_var(t_mother *s, char *str)
{
	int		i;
	int		len;
	int		pos;

	i = 0;
	len = ft_strlen_array(s->var);
	pos = -1;
	while (i < len)
	{
		if (ft_env_cmp(s->var[i], str))
			pos = i;
		i++;
	}
	if (pos == -1)
		add_var(s, str);
	else
		change_var(s, str, pos);
}

void	change_var(t_mother *s, char *str, int pos)
{
	char	**temp;
	int		i;
	int		len;

	len = ft_strlen_array(s->var);
	temp = ft_malloc(&temp, (len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		if (i == pos)
			temp[i] = ft_strdup(str);
		else
			temp[i] = ft_strdup(s->var[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_array(s->env);
	s->var = temp;
}

void	add_var(t_mother *s, char *str)
{
	char	**temp;
	int		i;
	int		len;

	len = ft_strlen_array(s->var);
	temp = ft_malloc(&temp, (len + 2) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		temp[i] = ft_strdup(s->var[i]);
		i++;
	}
	temp[i++] = ft_strdup(str);
	temp[i] = NULL;
	ft_free_array(s->env);
	s->var = temp;
}

void	rm_var(t_mother *s, char *str)
{
	char	**temp;
	int		i;
	int		len;

	len = ft_strlen_array(s->var);
	temp = ft_malloc(&temp, (len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		if (!(ft_env_cmp_arg(s->var[i], str)))
			temp[i] = ft_strdup(s->var[i]);
		i++;
	}
	temp[i] = NULL;
	ft_free_array(s->env);
	s->var = temp;
}
