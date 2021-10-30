#include "../../inc/minishell.h"

int	ft_find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	env_replacing_rest(t_mother *s, t_token *tok, int i)
{
	char	*temp;

	if (i == 1)
	{
		free(tok->token);
		tok->token = ft_malloc(tok->token, sizeof(char));
		tok->token[0] = '\0';
	}
	else if (i == 2)
	{
		temp = ft_substr(tok->token, 1, ft_strlen(tok->token) - 1);
		free(tok->token);
		tok->token = ft_return_env_value(s, temp, 1);
		free(temp);
	}
}

void	env_replacing_equal_sign(t_mother *s, t_token *tok)
{
	int		equal_sign;
	char	*temp;
	char	*temp_2;

	equal_sign = ft_find_equal_sign(tok->token);
	temp = ft_substr(tok->token, 1, equal_sign - 1);
	temp_2 = ft_return_env_value(s, temp, 1);
	free(temp);
	temp = ft_substr(tok->token, equal_sign, ft_strlen(tok->token)
			- equal_sign);
	free(tok->token);
	tok->token = ft_strjoin(temp_2, temp);
	free(temp);
	free(temp_2);
}

int	quote_env_finder(t_token *tok)
{
	int		i;

	i = 0;
	while (tok->token[i])
	{
		if (tok->token[i] == '$' && tok->token[i + 1] != '\0'
			&& tok->token[i + 1] != ' ')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin_env(char *str1, char *str2)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	len = ft_strlen(str1) + ft_strlen(str2);
	res = ft_malloc(&res, (len + 1) * sizeof(char));
	i = 0;
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		res[i + j] = str2[j];
		j++;
	}
	res[i + j] = '\0';
	free(str1);
	return (res);
}
