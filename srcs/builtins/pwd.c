/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:23:02 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 10:17:46 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_mother *s)
{
	char	temp[1000];
	
	(void)s;
	if (getcwd(temp, sizeof(temp)) == NULL)
	{
		perror("pwd");
		return (-1);
	}
	else
		// ft_putstr_fd(temp, 0);
	printf("%s\n", temp);

	return (0);
}