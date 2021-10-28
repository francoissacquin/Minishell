#include "../../inc/minishell.h"

int	miniparser(t_mother *s)
{
	t_token	*tok;
	int		i;
	int		res;

	tok = s->lex->first_token;
	i = 0;
	while (tok->next != NULL)
	{
		res = ft_tok_conveyor_belt(s, tok, &i);
		if (res)
		{
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
	if (*i == 0 && ft_strchr("Pfo", tok->type)
		&& ft_strcmp(tok->token, "<<") != 0 && s->lex->delimiter == NULL)
	{
		write(2, "Error, pipe or operator with no command\n", 40);
		s->ret = 1;
		err = 1;
	}
	else if (ft_strcmp(tok->token, "<<") == 0 && s->lex->delimiter == NULL)
	{
		s->ret = 2;
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
			if (ft_strchr("fq", tok->type)
				&& !(ft_strcmp(last->command, "echo")))
				check_echo_flag(s, tok);
			else if (tok->type == 'f')
				write(2, "AUCUN FLAG AUTORISE POUR LES BUILT-INS\n", 39);
		}
		last->nbarg++;
		if (tok->pre_space == 0 && tok->type == 'p'
			&& ft_strchr("pe", tok->prev->type))
			ft_add_arg_array(last, tok->token, 1);
		else if (last->command != NULL && tok->pre_space == 0
			&& !(ft_strcmp(last->command, "export")))
			ft_add_arg_array(last, tok->token, 1);
		else
			ft_add_arg_array(last, tok->token, 0);
		if (last->line == NULL)
			last->line = ft_strdup(tok->token);
		else
		{
			if (last->command != NULL && !(ft_strcmp(last->command, "export"))
				&& tok->pre_space == 0)
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
	char	**temp;
	char	*append_temp;
	int		len;
	int		i;

	len = ft_strlen_array(last->arg);
	if (type == 0)
		temp = ft_malloc(&temp, (len + 2) * sizeof(char *));
	else if (type == 1)
		temp = ft_malloc(&temp, (len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		temp[i] = ft_strdup(last->arg[i]);
		i++;
	}
	if (type == 0)
	{
		temp[i] = ft_strdup(str);
		i++;
	}
	else if (type == 1)
	{
		i--;
		append_temp = ft_strdup(temp[i]);
		free(temp[i]);
		temp[i] = ft_strjoin(append_temp, str);
		free(append_temp);
		i++;
	}
	temp[i] = NULL;
	ft_free_array(last->arg);
	last->arg = temp;
}

int	ft_add_operator(t_mother *s, t_token *tok, int *i)
{
	t_command	*last;

	last = ft_last_cmd(s->c);
	if (tok->type == 'P')
	{
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
				write(2, "pipe leads to non valid command\n", 32);
				s->ret = 1;
				return (1);
			}
		}
		else
		{
			write(2, "pipe is last token???\n", 22);
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
