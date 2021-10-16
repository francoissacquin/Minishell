/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:23:06 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/12 20:10:56 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_unset(t_mother *s, t_command *c)
{
	int		i;
	int		rm_switch;
	int		ret;

	if (ft_strlen_array(c->arg) != 2)
			return(0);
	//ft_error(s, "unset arg number invalid\n", 0); // a modifier pour la return value, c'est pas la bonne.
	i = 0;
	rm_switch = 0;
	// if (s->c->arg[1] == NULL)
	// {
	// 	return(0);
	// }
	
	while (s->env[i] != NULL)
	{
		if (ft_env_cmp_arg(s->env[i], c->arg[1]))
			rm_switch = 1;
		i++;
	}
	ret = 0;
	// REGARDER POUR LE CAS OU LA VALEUR A UNSET CONTIENT DES CARACTERES NON VALABLE : ret = 1.
	if (rm_switch == 1)
		rm_env(s, c->arg[1]);
	else if (ft_strchr(c->arg[1], ';'))
		ret = 127;
	else if (ft_word_is_exportable(c->arg[1]))
		ret = 0;
	else if (c->arg[1][0] == '-')
		ret = 2;
	else
		ret = 1;
	return(ret);
}