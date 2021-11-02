#include "../../inc/minishell.h"

void	expanding_env(t_mother *s, t_token *tok)
{
	int		index;
	char	*temp;

	index = quote_env_finder(tok);
	if (tok->type == 'q' && tok->token[0] == '\'')
	{
		temp = ft_substr(tok->token, 1, ft_strlen(tok->token) - 2);
		free(tok->token);
		tok->token = temp;
		return ;
	}
	while (index != -1)
		expanding_env_plus(s, tok, &index);
	if (tok->type == 'q')
	{
		temp = ft_substr(tok->token, 1, ft_strlen(tok->token) - 2);
		free(tok->token);
		tok->token = temp;
	}
}

void	expanding_env_plus(t_mother *s, t_token *tok, int *index)
{
	int		end;

	if (tok->type == 'q')
	{
		end = *index + 1;
		while (tok->token[end] && (ft_isalnum(tok->token[end])
				|| tok->token[end] == '_'))
			end++;
		quote_env_replacing(s, tok, *index, end);
	}
	else if (tok->type == 'e')
		env_replacing(s, tok);
	*index = quote_env_finder(tok);
}

void	quote_env_replacing(t_mother *s, t_token *tok, int start, int end)
{
	char	*temp;
	char	*value;

	if (ft_isdigit(tok->token[start + 1]))
	{
		if (tok->token[start + 2] == '\'')
			temp = ft_strdup("\'");
		else if (tok->token[start + 2] == '\"')
			temp = ft_strdup("\"");
		else
			temp = ft_substr(tok->token, start + 2, ft_strlen(tok->token)
					- (start + 2));
		value = ft_substr(tok->token, 0, start);
		value = ft_strjoin_env(value, temp);
		free(temp);
		free(tok->token);
		tok->token = value;
		return ;
	}
	quote_env_replacing_plus(s, tok, start, end);
}

void	quote_env_replacing_plus(t_mother *s, t_token *tok, int start, int end)
{
	int		len;
	char	*temp;
	char	*value;

	len = ft_strlen(tok->token);
	temp = ft_substr(tok->token, start + 1, end - start - 1);
	value = ft_return_env_value(s, temp, 1);
	free(temp);
	temp = ft_substr(tok->token, 0, start);
	temp = ft_strjoin_env(temp, value);
	free(value);
	value = ft_substr(tok->token, end, len - end);
	temp = ft_strjoin_env(temp, value);
	free(value);
	free(tok->token);
	tok->token = temp;
}

void	env_replacing(t_mother *s, t_token *tok)
{
	char	*temp;

	if (ft_isdigit(tok->token[1]))
	{
		if (tok->token[2] == '\0')
			env_replacing_rest(s, tok, 1);
		else
		{
			temp = ft_substr(tok->token, 2, ft_strlen(tok->token) - 2);
			free(tok->token);
			tok->token = temp;
		}
	}
	else if (ft_find_equal_sign(tok->token) > -1)
		env_replacing_equal_sign(s, tok);
	else if (!(ft_strcmp("$?", tok->token)))
	{
		free(tok->token);
		tok->token = ft_itoa(s->ret);
	}
	else
		env_replacing_rest(s, tok, 2);
}
