/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:22 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/06 11:49:39 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define	MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"

typedef struct s_mother	t_mother;
typedef struct s_command t_command;


typedef struct s_command
{
	char 		*line; //the whole string inbetween separators

	char		*command;
	int			retvalue; // check how it shuld be done char*..?

	int			nbarg;
	char		**arg;
	
	int			isfollowedbypipe;	//pipe handling
	t_command	*nextpipe;
	int			isprecededbypipe;
	t_command	*previouspipe;

	int			isoutfile; //boolean checking for a specific output default is stdout
	char		*outfile;  //path to outfile
	int			isinputfile; //boolean checking for a specific input default is stdin
	char		*inputfile;  //path to input file

	int			iserrofile; //check if necessary with subject
	char		*errorfile;

}				t_command;

typedef struct s_mother
{
	char 		*line; //whole string received
	int			nbcmd; //numberof commands
	int			pipe; //number of pipes
	int			exitret; // value for the exit command to be updated during execution
	char		*path;
	t_command	*c;

	

}				t_mother;

//general
int		ft_parse(t_mother *s);
void	ft_structinit(t_mother *s);
void	ft_end(t_mother *s);
void	ft_error(t_mother *s, char * error, int code);
//builtins
void	ft_echo(t_mother *s);
int		ft_cd(t_mother *s);
int		ft_pwd(t_mother *s);
void	ft_env(t_mother *s);
void 	ft_export(t_mother *s);
void 	ft_unset(t_mother *s);
//exec
void	ft_execfind(t_mother *s);
void	ft_execnotbuiltin(t_mother *s);
char	*ft_pathfinder(t_mother *s);







#endif
