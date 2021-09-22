#include "../../inc/minishell.h"

void	redir_input_handler(t_mother *s)
{
	t_token		*tok;

	tok = s->lex->first_token;
	while(tok->next != NULL)
	{
		if (!(ft_strcmp(tok->token, "<<")) && tok->type == 'o')
		{
			//LANCER LE READLINE EN BOUCLE
			ft_finding_delimiter(s, tok);
			ft_redir_error_check(s, tok);
			//ft_redir_input_activator(s, tok);
		}
	}
}

void	ft_finding_delimiter(t_mother *s, t_token *tok)
{
	char	*temp;

		
}

void	ft_redir_error_check(t_mother *s, t_token *tok)
{
	if (tok->next == NULL)
		printf("DELIMITER IS MISSING FROM << REDIR\n"); // METTRE FT_ERROR ICI
	else if (ft_strchr(tok->next->type)
		printf("cool");
}
