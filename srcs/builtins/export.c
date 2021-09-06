/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:59 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 10:21:41 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_export(t_mother *s)
{
	if (ft_strlen_array(s->c->arg) != 1)
	{
		ft_error(s, "export arg value invalid\n", 0); // a modifier pour la return value, c'est pas la bonne.
	}
	create_env(s, s->c->arg[0]);
}