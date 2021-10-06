#include "../../inc/minishell.h"

void	assign_types(t_mother *s)
{
	t_token	*temp;

	temp = s->lex->first_token;
	while (temp != NULL)
	{
		if (temp->type == 'S')
			ft_error(s, "Error, input should not contain a delimiter\n", 1);
		if (temp->type == '\0' && temp->token != NULL)
		{
			ft_type_flag(temp);
			ft_type_env(temp);
			ft_type_path(s, temp);
			ft_type_cmd(s, temp);
			ft_type_built(temp);
		}
		if (temp->type == 'o')
			ft_type_pipe(temp);
		if (temp->type == '\0')
			temp->type = 'w';
		temp = temp->next;
	}
}

void	ft_type_flag(t_token *tok)
{
	int		i;

	i = 1;
	if (tok->token[0] == '-')
	{
		while (tok->token[i])
		{
			if (!(ft_isalpha(tok->token[i])))
				return ;
			i++;
		}
		tok->type = 'f';
	}
}

//Using POSIX standards on shells section of IEEE Std 1003.1-2008 / IEEE POSIX P1003.2/ISO 9945.2 Shell and Tools standard
void	ft_type_env(t_token *tok)
{
	int		i;

	i = 1;
	if (tok->token[0] == '$')
	{
		while (tok->token[i] && tok->token[i] != '=')
		{
			if (!(ft_isalnum(tok->token[i]) || tok->token[i] == '_'))
				return ;
			i++;
		}
		if (tok->token[i] == '\0')
			tok->type = 'e';
	}
	else
	{
		i = 0;
		while (tok->token[i] && tok->token[i] != '=')
		{
			if (!(ft_isalnum(tok->token[i]) || tok->token[i] == '_'))
				return ;
			i++;
		}
		if (tok->token[i] != '=')
			return;
		i++;
		while (tok->token[i] && tok->token[i] != '=')
		{
			if (!(ft_isalnum(tok->token[i]) || tok->token[i] == '_'))
				return ;
			i++;
		}
		tok->type = 'E';
	}
}

void	ft_type_built(t_token *tok)
{
	if (!(ft_strcmp(tok->token, "echo")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "cd")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "pwd")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "export")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "unset")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "env")))
		tok->type = 'b';
	else if (!(ft_strcmp(tok->token, "exit")))
		tok->type = 'b';
	else
		return ;
}

void	ft_type_pipe(t_token *tok)
{
	if (!(ft_strcmp(tok->token, "|")))
		tok->type = 'P';
}


void	ft_type_cmd(t_mother *s, t_token *tok)
{
	char	**array;
	int		i;
	int		exist;
	char	*temp;

	temp = ft_return_env_value(s, "PATH", 1);
	array = ft_split(temp, ':');
	free(temp);
	i = 0;
	if (tok->type == 'p')
		return ;
	while (array[i] != NULL)
	{
		//printf("||%s||\n", ft_strjoin(array[i], ft_strjoin("/", tok->token)));
		exist = ft_stat_check(array[i], tok);
		if (exist == 0)
		{
			tok->type = 'c';
			ft_free_array(array);
			return ;
		}
		i++;
	}
	ft_free_array(array);
}

int		ft_stat_check(char *path, t_token *tok)
{
	char	*temp;
	char	*temp_2;
	struct stat	sb;
	int		i;

	temp = ft_strjoin("/", tok->token);
	temp_2 = ft_strjoin(path, temp);
	i = stat(temp_2, &sb);
	free(temp);
	free(temp_2);
	return (i);
}

void	ft_type_path(t_mother *s, t_token *tok)
{
	int		i;
	char	*temp;
	char	*inter;

	(void)s; // A ENLEVER
	i = 0;
	if (ft_strchr("./~", tok->token[0]))
		tok->type = 'p';
	while (tok->token[i])
	{
		if (tok->token[i] == '~')
		{
			temp = ft_strdup(tok->token);
			free(tok->token);
			inter = ft_strjoin(ft_substr(temp, 0, i), ft_return_env_value(s, "HOME", 1));
			tok->token = ft_strjoin(inter, &temp[i + 1]);
			free(inter);
			free(temp);
		}
		i++;
	}
	i = 0;
	while (tok->token[i])
	{
		if (tok->token[i] == '/')
			tok->type = 'p';
		i++;
	}
}
