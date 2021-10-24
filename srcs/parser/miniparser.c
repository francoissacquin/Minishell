#include "../../inc/minishell.h"

int		miniparser(t_mother *s)
{
	t_token	*tok;
	int		i;
	int		res;

	tok = s->lex->first_token;
	i = 0;
	while(tok->next != NULL)
	{
		res = ft_tok_conveyor_belt(s, tok, &i);
		if (res)
		{
			//ft_print_parsing_results(s);
			ft_wrong_input(s);
			return (1);
		}
		tok = tok->next;
		i++;
	}
	if (tok->token != NULL)
	{
		res = ft_tok_conveyor_belt(s, tok, &i);
		if (res)
		{
			//ft_print_parsing_results(s);
			ft_wrong_input(s);
			return (1);
		}
	}
	return (0);
}

int	ft_tok_conveyor_belt(t_mother *s, t_token *tok, int *i)
{
	int		err;

	err = 0;
	if (*i == 0 && ft_strchr("Pfo", tok->type) && (!(ft_strcmp(tok->token, "<<")) && s->lex->delimiter == NULL))
	{
		write(2, "Error, pipe with no prior command\n", 34);
		s->ret = 1;
		err = 1;
	}
	else if (tok->type == 'p' && (*i == 0 || tok->prev->type == 'P'))
	{
		write(2, "Minishell: commande introuvable\n", 32);
		s->ret = 127;
		err = 1;
	}
	else if (*i == 0 && tok->type == 'w')
	{
		write(2, "Error, weird input\n", 19);
		s->ret = 127;
		err = 1;
	}
	else if (ft_strchr("cb", tok->type))
		ft_cmd_blt(s, tok, i);
	else if (ft_strchr("Po", tok->type))
		err = ft_add_operator(s, tok, i);
	else if (ft_strchr("wpfdEeq", tok->type) && s->redirect_mem == 0)
		ft_add_args(s, tok, i);
	else if (ft_strchr("wpeq", tok->type) && s->redirect_mem != 0)
		ft_cmd_blt(s, tok, i);
	return (err);
}

void	ft_cmd_blt(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;
	int			fd;

	last = ft_last_cmd(s->c);
	//printf("pour passage %i on a s->redir = %i\n", *i, s->redirect_mem);
	if (s->redirect_mem == 5 && tok->next != NULL)
	{
		if (tok->next != NULL && ft_strchr("bc", tok->next->type) && last == s->c)
		{
			fill_first_command(s, tok->next);
			plug_redir_5(s, s->c);
		}
		else if (tok->next != NULL && ft_strchr("bc", tok->next->type) && last != s->c)
		{
			fill_next_command(s, last, tok->next, i);
			last = ft_last_cmd(s->c);
			plug_redir_5(s, last);
		}
		else
		{
			if (last->inputfile == NULL)
				plug_redir_5(s, last);
			s->redirect_mem = 0;

		}
	}
	else if (tok->prev != NULL && last->line != NULL)
	{
		if (tok->prev->type == 'P')
		{
			//printf("--creation post pipe avec s->redir = %i\n", s->redirect_mem);
			fill_next_command(s, last, tok, i);
		}
		else if (s->redirect_mem == 5)
			plug_redir_5(s, last);
		else if (s->redirect_mem == 2)
		{
			last->isinputfile = 1;
			if (last->inputfile != NULL)
			{
				free(last->inputfile);
				last->isprecededbydoubleche = 0;
			}
			last->inputfile = ft_strdup(tok->token);
			last->isprecededbyche = 1;
			s->redirect_mem = 0;
		}
		else if (s->redirect_mem == 3 || s->redirect_mem == 4)
		{
			last->isoutfile = 1;
			fd = open(tok->token, O_CREAT | O_RDWR | O_APPEND, 0666);
			close(fd);
			if (last->outfile != NULL)
			{
				free (last->outfile);
				last->outfile = NULL;
			}
			last->outfile = ft_strdup(tok->token);
			if (s->redirect_mem == 3)
			{
				last->isfollowedbydoubleche = 0;
				last->isfollowedbyche = 1;
			}
			else if (s->redirect_mem == 4)
			{
				last->isfollowedbyche = 0;
				last->isfollowedbydoubleche = 1;
			}
			s->redirect_mem = 0;
		}
		else
		{
			tok->type = 'w';
			ft_add_args(s, tok, i);
		}
	}
	else
	{
		//printf("--creation premier element avec s->redir = %i\n", s->redirect_mem);
		fill_first_command(s, tok);
	}
}

void	plug_redir_5(t_mother *s, t_command *last)
{
	char	*temp;
	int			fd;

	if (last->inputfile != NULL)
		free(last->inputfile);
	last->isprecededbyche = 0;
	fd = open("redir_input.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd < 0)
		s->ret = 1;
	write(fd, s->lex->std_input_redir, ft_strlen(s->lex->std_input_redir));
	close(fd);
	last->isinputfile = 1;
	temp = getenv("PWD");
	last->inputfile = ft_strdup("redir_input.txt");
	last->isprecededbydoubleche = 1;
}

void	fill_next_command(t_mother *s, t_command *last, t_token *tok, int *i)
{
	t_command	*next;

	last->isfollowedbypipe = 1;
	add_cmd_elem(s, tok, i);
	next = ft_last_cmd(s->c);
	last->nextpipe = next;
	next->previouspipe = last;
	next->nextpipe = NULL;
	next->isprecededbypipe = 1;
	next->isprecededbyche = 0;
	next->isprecededbydoubleche = 0;
	next->isfollowedbypipe = 0;
	next->isfollowedbyche = 0;
	next->isfollowedbydoubleche = 0;
	next->isinputfile = 0;
	next->inputfile = NULL;
	next->isoutfile = 0;
	next->outfile = NULL;
	s->pipe++;
}

void	fill_first_command(t_mother *s, t_token *tok)
{
	s->c->command = ft_strdup(tok->token);
	s->c->line = ft_strdup(tok->token);
	s->c->retvalue = 0;
	s->c->nbarg = 1;
	s->c->arg = ft_malloc(&s->c->arg, sizeof(char *) * 2);
	s->c->arg[0] = ft_strdup(tok->token);
	s->c->arg[1] = NULL;
	s->c->cmd_status = tok->type - 97;
	s->nbcmd++;
}

int	ft_add_args(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;
	char		*temp;
	char		*temp_line;

	(void)i;
	last = ft_last_cmd(s->c);
	pre_exec_arg_checking(s, last, tok);
	if (ft_strchr("pwfqeE", tok->type))
	{
		if (last->cmd_status == 1)
		{
			if (ft_strchr("fq", tok->type) && !(ft_strcmp(last->command, "echo")))
				check_echo_flag(s, tok);
			else if (tok->type == 'f')
				write(2, "AUCUN FLAG AUTORISE POUR LES BUILT-INS\n", 39);
		}
		last->nbarg++;
		if (tok->pre_space == 0 && tok->type == 'p' && ft_strchr("pe", tok->prev->type))
			ft_add_arg_array(last, tok->token, 1);
		else if (last->command != NULL && tok->pre_space == 0 && !(ft_strcmp(last->command, "export")))
			ft_add_arg_array(last, tok->token, 1);
		else
			ft_add_arg_array(last, tok->token, 0);
		if (last->line == NULL)
			last->line = ft_strdup(tok->token);
		else
		{
			if (last->command != NULL && !(ft_strcmp(last->command, "export")) && tok->pre_space == 0)
				temp = ft_strdup(tok->token);
			else
				temp = ft_strjoin(" ", tok->token);
			temp_line = ft_strdup(last->line);
			free(last->line);
			last->line = ft_strjoin(temp_line, temp);
			free(temp);
			free(temp_line);
		}
	}
	return (0);
}

void	ft_add_arg_array(t_command *last, char *str, int type)
{
	char 	**temp;
	char	*append_temp;
	int		len;
	int		i;

	len = ft_strlen_array(last->arg);
	i = 0;
	while(last->arg[i] != NULL)
	{
		printf("pre-arg:%s\n", last->arg[i]);
		i++;
	}
	printf("type of add_arg = %i and len = %i\nchar is ||%s||\n", type, len, str);
	if (type == 0)
		temp = ft_malloc(&temp, (len + 2) * sizeof(char *));
	else if (type == 1)
		temp = ft_malloc(&temp, (len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		temp[i] = ft_strdup(last->arg[i]);
		printf(">>%s<<\n", temp[i]);
		i++;
	}
	if (type == 0)
	{
		temp[i] = ft_strdup(str);
		printf(">>%s<<\n", temp[i]);
		i++;
	}
	else if (type == 1)
	{
		i--;
		append_temp = ft_strdup(temp[i]);
		free(temp[i]);
		temp[i] = ft_strjoin(append_temp, str);
		printf(">>%s<<\n", temp[i]);
		free(append_temp);
		i++;
	}
	temp[i] = NULL;
	printf("len after adding %zu\n", ft_strlen_array(temp));
	ft_free_array(last->arg);
	last->arg = temp;
}

int	ft_add_operator(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	last = ft_last_cmd(s->c);
	if (tok->type == 'P')
	{
		//check that last command structure is completed and next token is actually a command
		if (last->line == NULL || last->command == NULL || last->arg == NULL)
		{
			write(2, "wrong pipe here, last command does not exist\n", 45);
			s->ret = 1;
			return (1);
		}
		if (tok->next != NULL)
		{
			if (ft_strchr("bc", tok->next->type))
				return (0);
			else
			{
				write(2, "pipe leads to non valid command\n", 32); //METTRE FT_ERROR ICI
				s->ret = 1;
				return (1);
			}
		}
		else
		{
			write(2, "pipe is last token???\n", 22); //METTRE FT_ERROR ICI
			s->ret = 1;
			return (1);
		}
		
	}
	else if (tok->type == 'o')
	{
		if (tok->next != NULL)
		{
			if (ft_strchr("bcwep", tok->next->type))
				assign_redirect(s, tok, i);
			else
			{
				write(2, "Error, operator cannot take this argument\n", 42);
				s->ret = 1;
				return (1);
			}
		}
		if (tok->prev != NULL)
		{
			if (last->line != NULL && ft_strrchr("bcwefpq", tok->prev->type))
				assign_redirect(s, tok, i);
		}
	}
	return (0);
}

void	assign_redirect(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	(void)i;
	last = ft_last_cmd(s->c);
	if (!(ft_strcmp(tok->token, "<")))
		s->redirect_mem = 2;
	else if (!(ft_strcmp(tok->token, ">")))
		s->redirect_mem = 3;
	else if (!(ft_strcmp(tok->token, ">>")))
		s->redirect_mem = 4;
	else if (!(ft_strcmp(tok->token, "<<")))
		s->redirect_mem = 5;
}

void	add_cmd_elem(t_mother *s, t_token *tok, int *i)
{
	t_command	*next;
	t_command	*prev;

	//printf("creating new cmd element with i = %i\n", *i);
	prev = ft_last_cmd(s->c);
	if (prev->command != NULL)
	{
		//check_pipe(); checking the existence of a pipe and creating a new cmd in case the pipe exists
		next = create_cmd(s, tok, i);
		next->previouspipe = prev;
		prev->nextpipe = next;
		next->nextpipe = NULL;
	}
	else
	{
		s->c = create_cmd(s, tok, i);
		s->c->previouspipe = NULL;
		s->c->nextpipe = NULL;
	}
}

t_command	*create_cmd(t_mother *s, t_token *tok, int *i)
{
	t_command	*new;

	(void)i;
	(void)s;
	new = ft_malloc(&new, sizeof(t_command));
	new->command = ft_strdup(tok->token);
	new->line = ft_strdup(tok->token);
	new->retvalue = 0;
	new->nbarg = 1;
	new->arg = ft_malloc(&new->arg, sizeof(char *) * 2);
	new->arg[0] = ft_strdup(tok->token);
	new->arg[1] = NULL;
	new->cmd_status = tok->type - 97;
	s->nbcmd++;
	return (new);
}

t_command	*ft_last_cmd(t_command *first)
{
	t_command	*temp;

	temp = first;
	while (temp->nextpipe != NULL)
		temp = temp->nextpipe;
	return (temp);
}

void	ft_wrong_input(t_mother *s)
{
	free_t_token(s);
	free_t_cmd(s);
	free_t_lexer(s);
	//printf("INPUT NON VALIDE\n"); // METTRE FT_ERROR ICI
}
