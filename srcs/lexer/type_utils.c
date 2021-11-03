/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:20:59 by ogenser           #+#    #+#             */
/*   Updated: 2021/11/03 20:21:01 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_op_redir(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!(ft_strchr("<>|", str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_stat_check_path(char *str)
{
	int			i;
	struct stat	sb;

	i = stat(str, &sb);
	return (i);
}

int	ft_type_abs_cmd(t_token *tok)
{
	int		exist;

	if (tok->type == 'p')
	{
		exist = ft_stat_check_path(tok->token);
		if (exist == 0)
		{
			tok->type = 'C';
			return (1);
		}
	}
	return (0);
}
