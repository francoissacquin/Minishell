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

int	ft_unset(t_mother *s, t_command *c)
{
	int		j;
	int		rm_switch;
	int		ret;

	if (ft_strlen_array(c->arg) < 2)
		return (0);
	j = 1;
	while (c->arg[j])
	{
		rm_switch = ft_search_and_destroy(s, c, j);
		ret = 0;
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
		j++;
	}
	return (ret);
}

int	ft_search_and_destroy(t_mother *s, t_command *c, int j)
{
	int		i;
	int		rm_switch;

	i = 0;
	rm_switch = 0;
	while (s->env[i] != NULL)
	{
		if (ft_env_cmp_arg(s->env[i], c->arg[j]))
			rm_switch = 1;
		i++;
	}
	return (rm_switch);
}
