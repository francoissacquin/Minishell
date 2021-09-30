/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:56 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 10:21:31 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//missing 
//find how to make the return of a command to a number
// export to superior level of shell so it's accessible after being exited with echo $?

int ft_exit(t_mother *s)
{
	ft_end(s);
	exit(s->ret);
}
