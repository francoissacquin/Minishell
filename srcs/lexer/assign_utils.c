/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:20:06 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:20:17 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_check_env_value(t_token *tok, int *i)
{
	while (tok->token[*i] && !(ft_strchr("+=", tok->token[*i])))
	{
		if (ft_isdigit(tok->token[*i]) && *i == 0)
			return ;
		else if (ft_env_char_check(tok->token[*i]))
			return ;
		*i = *i + 1;
	}
	if (tok->token[*i] == '=' && *i == 0)
		return ;
	if (tok->token[*i] == '+')
		*i = *i + 1;
	if (tok->token[*i] != '=')
		return ;
	*i = *i + 1;
	while (tok->token[*i] && tok->token[*i] != '=')
	{
		if (!(ft_isalnum(tok->token[*i]) || tok->token[*i] == '_'
				|| tok->token[*i] == ' '))
			return ;
		*i = *i + 1;
	}
	tok->type = 'E';
}

int	ft_env_char_check(char c)
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

int	ft_stat_check(char *path, t_token *tok)
{
	char		*temp;
	char		*temp_2;
	struct stat	sb;
	int			i;

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

	(void)s;
	i = 0;
	if (ft_strchr("./", tok->token[0]))
		tok->type = 'p';
	else if ((tok->token[0] == '~' && tok->token[1] == '/')
		|| !(ft_strcmp(tok->token, "~")))
	{
		while (tok->token[i])
		{
			if (tok->token[i] == '~')
				expanding_home(s, tok, i);
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

void	expanding_home(t_mother *s, t_token *tok, int i)
{
	char	*temp;
	char	*value;
	char	*inter;

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
