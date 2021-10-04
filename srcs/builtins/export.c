/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:59 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/08 11:03:32 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_export(t_mother *s, t_command *cmd)
{
	int ret = 1;

	if (ft_strlen_array(cmd->arg) != 2)
	{
		ft_error(s, "export arg number invalid\n", 0); // a modifier pour la return value, c'est pas la bonne.
	}
	create_env(s, cmd->arg[1]);
	return(ret);
}