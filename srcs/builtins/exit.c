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
	int lastcommandfail = 0;
	char *arg = "2";
	int retvalue;
	
	retvalue = 0;
	exit(2);

	if (arg /*&& ft_isdigit(arg) >= 1*/) // check we only send digits -> parsing
		retvalue = ft_atoi(arg);
	else if (lastcommandfail == 1 && arg)
		retvalue = 0;					//find right return value for case
	else if (lastcommandfail == 0 && arg)
		retvalue = 0;					//find right return value for case
	else
	{
		retvalue = 0;
	}
	//set value in env
	//send retrun value
	return(retvalue);
	ft_end(s);
	//
}
