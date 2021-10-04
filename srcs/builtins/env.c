/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:53 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 10:20:50 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_env(t_mother *s)
{
	int		i;
	int		ret;

	i = 0;
	while (s->env[i] != NULL)
	{
		ft_putstr_fd(s->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	ret = 0;
	return(ret);
}