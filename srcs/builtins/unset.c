/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:23:06 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/08 11:03:51 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_unset(t_mother *s)
{
	int		i;
	int		rm_switch;
	int		ret = 1;

	if (ft_strlen_array(s->c->arg) != 1)
		ft_error(s, "unset arg value invalid\n", 0); // a modifier pour la return value, c'est pas la bonne.
	i = 0;
	rm_switch = 0;
	while (s->env[i] != NULL)
	{
		if (ft_env_cmp_arg(s->env[i], s->c->arg[1]))
			rm_switch = 1;
		i++;
	}
	if (rm_switch != 0)
		rm_env(s, s->c->arg[1]);
	else
		ft_error(s, "unser arg does not exist in env\n", 0); // a modifier pour le 0 egalement
	return(ret);
}