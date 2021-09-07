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
	int			retvalue; // check how it should be done char*..?

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

typedef struct s_token
{
	char		*token;
	char		type;
	s_lexer		*prev;
	s_lexer		*next;
}				t_token;

typedef struct s_lexer
{
	t_token		*first_token;
	int			quote; // a simple int to store info on quote input history for quotation rules
}

typedef struct s_mother
{
	char 		*line; //whole string received
	t_lexer		*lex; // pointer to the structure of tokens for input;
	char		**env; //char ** containing environment variables (useful for env and execve() PATHS)
	int			nbcmd; //numberof commands
	int			pipe; //number of pipes
	int			exitret; // value for the exit command to be updated during execution
	char		*path; //env variable value for PATH
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
//env
void	env_init(t_mother *s, char **envp);
void	create_env(t_mother *s, char *str);
void	change_env(t_mother *s, char *str, int pos);
void	add_env(t_mother *s, char *str);
void	rm_env(t_mother *s, char *str);
//env_utils
size_t	ft_strlen_array(char **array);
void	ft_free_array(char **array);
int		ft_env_cmp(char *env1, char *var);
int		ft_env_cmp_arg(char *env1, char *var);







#endif
