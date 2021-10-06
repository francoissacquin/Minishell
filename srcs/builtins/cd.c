/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:22:46 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 10:20:22 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


//cd home
// cd with deleted . directory
// replace pwd
// max size of filename is 255 bytes
// cd - et cd ~
// handle number of args

int		ft_cd(t_mother *s)
{
	char *arg = "../minishell/srcs"; //received as argument after parsing
	char path[1000];
	char targetpath[1000];
	int		r = 0;
	
	(void)s;
	ft_memset(path, 0, sizeof(path));
	ft_memset(targetpath, 0, sizeof(targetpath));
	getcwd(path, sizeof(path));
	r = chdir(arg);
	if (r == -1)
		ft_error(s, "chdir failed", -1);
	getcwd(targetpath, sizeof(targetpath));
	ft_pwd(s);
	//printf("%s r = %d", targetpath, r);
	return(0);
}