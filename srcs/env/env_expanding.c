#include "../../inc/minishell.h"

void	expanding_env(t_mother *s, t_token *tok)
{
	int		index;
	int		end;

	index = quote_env_finder(tok);
	if (tok->type == 'q' && tok->token[0] == '\'')
		return ;
	while (index != -1)
	{
		printf("entering here\n");
		if (tok->type == 'q')
		{
			end = index + 1;
			while (tok->token[end] && (ft_isalnum(tok->token[end]) || tok->token[end] == '_'))
				end++;
			quote_env_replacing(s, tok, index, end);
		}
		else if (tok->type == 'e')
			env_replacing(s, tok);
		index = quote_env_finder(tok);
	}
}

void	quote_env_replacing(t_mother *s, t_token *tok, int start, int end)
{
	int		len;
	char	*temp;
	char	*value;

	len = ft_strlen(tok->token);
	temp = ft_substr(tok->token, start + 1, end - start - 1);
	printf("searchin with temp = %s\n", temp);
	value = ft_return_env_value(s, temp, 1);
	printf(" ======>%s\n", value);
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

	printf("NANIIIIIIIIIII\n");
	temp = ft_substr(tok->token, 1, ft_strlen(tok->token) - 1);
	free(tok->token);
	tok->token = ft_return_env_value(s, temp, 1);
	free(temp);
}

int	quote_env_finder(t_token *tok)
{
	int		i;

	i = 0;
	while (tok->token[i])
	{
		if (tok->token[i] == '$')
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
