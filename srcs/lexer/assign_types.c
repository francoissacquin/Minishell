#include "../../inc/minishell.h"

void	assign_types(t_mother *s)
{
	t_token	*temp;

	temp = s->lex->first_token;
	while (temp != NULL)
	{
		if (temp->type == 'S')
			write(2, "Error, input should not contain a separator\';\'\n", 47);
		if (temp->type == '\0' && temp->token != NULL)
		{
			ft_type_flag(temp);
			ft_type_env(temp);
			ft_type_path(s, temp);
			ft_type_cmd(s, temp);
			ft_type_built(temp);
			ft_type_op(temp);
		}
		if (temp->type == 'e' && temp->token[1] == '?')
		{
			ft_env_tok_overflow(temp, 2);
		}
		if (temp->type == 'o')
			ft_type_pipe(temp);
		if (temp->type == '\0')
			temp->type = 'w';
		if (temp->type == 'q' || temp->type == 'e')
			expanding_env(s, temp);
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

void	ft_env_tok_overflow(t_token *tok, int limiter)
{
	t_token	*new;
	char	*temp;
	char	*temp2;

	temp = ft_substr(tok->token, limiter, ft_strlen(tok->token) - 2);
	if (tok->next != NULL)
	{
		temp2 = ft_strdup(tok->next->token);
		free(tok->next->token);
		tok->next->token = ft_strjoin(temp, temp2);
		tok->next->pre_space = 0;
		free(temp);
		free(temp2);
	}
	else
	{
		new = ft_malloc(&new, sizeof(t_token));
		new->token = temp;
		new->type = '\0';
		new->pre_space = 0;
		new->prev = tok;
		new->next = NULL;
		tok->next = new;
	}
	temp2 = ft_substr(tok->token, 0, 2);
	free(tok->token);
	tok->token = temp2;
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
		while (tok->token[i] && !(ft_strchr("+=",tok->token[i])))
		{
			if (ft_isdigit(tok->token[i]) && i == 0)
				return ;
			else if (ft_env_char_check(tok->token[i]))
				return ;
			i++;
		}
		if (tok->token[i] == '=' && i == 0)
			return ;
		if (tok->token[i] == '+')
			i++;
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

int		ft_env_char_check(char c)
{
	if (ft_isalnum(c))
		return (0);
	else if (c == '_')
		return (0);
	else if (c == '\\')
		return (0);
	else
		return (1);
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

void	ft_type_op(t_token *tok)
{
	if (!(ft_strcmp(tok->token, "<")))
		tok->type = 'o';
	else if (!(ft_strcmp(tok->token, "<<")))
		tok->type = 'o';
	else if (!(ft_strcmp(tok->token, ">")))
		tok->type = 'o';
	else if (!(ft_strcmp(tok->token, ">>")))
		tok->type = 'o';
	else if (ft_is_op_redir(tok->token))
		tok->type = 'o';
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
	{
		ft_free_array(array);
		return ;
	}
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
	char	*value;
	char	*inter;

	(void)s; // A ENLEVER
	i = 0;
	if (ft_strchr("./", tok->token[0]))
		tok->type = 'p';
	else if ((tok->token[0] == '~' && tok->token[1] == '/') || !(ft_strcmp(tok->token, "~")))
	{
		while (tok->token[i])
		{
			if (tok->token[i] == '~')
			{
				temp = ft_strdup(tok->token);
				free(tok->token);
				value = ft_return_env_value(s, "HOME", 1);
				tok->token = ft_substr(temp, 0, i);
				inter = ft_strjoin(tok->token, value);
				free(tok->token);
				free(value);
				tok->token = ft_strjoin(inter, &temp[i + 1]);
				free(inter);
				free(temp);
			}
			i++;
		}
		tok->type = 'p';
	}
	i = 0;
	while (tok->token[i])
	{
		if (tok->token[i] == '/')
			tok->type = 'p';
		i++;
	}
}
