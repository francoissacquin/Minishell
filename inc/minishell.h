/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:22 by ogenser           #+#    #+#             */
/*   Updated: 2021/09/16 21:10:43 by ogenser          ###   ########.fr       */
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
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_mother	t_mother;
typedef struct s_command t_command;
typedef struct s_lexer	t_lexer;
typedef struct s_token	t_token;


typedef struct s_command
{

	char 		*line; //the whole string inbetween separators //cat todo.txt
	char		*command;										//cat
	int			retvalue; // check how it should be done char*..?	//0
	int			cmd_status; //cmd_status is int for cmd info, 1 for built-ins, 2 for command, 22 for a non-command word.

	int			nbarg;												//1
	char		**arg; //arg[0] must be the command! and arg[last] must be null sinon bug de execve
	
	int			isfollowedbypipe;	//pipe handling 1 for a pipe, 2 for <, 3 for >, 4 for >>, 5 for <<, 6 for &, etc
	t_command	*nextpipe;
	int			isprecededbypipe;
	t_command	*previouspipe;

	int			isoutfile; //boolean checking for a specific output default is stdout
	char		*outfile;  //path to outfile
	int			isinputfile; //boolean checking for a specific input default is stdin
	char		*inputfile;  //path to input file

	int			iserrofile; //check if necessary with subject
	char		*errorfile;
	int			pipes[2];

}				t_command;

typedef struct s_token
{
	char		*token;
	char		type;
	t_token		*prev;
	t_token		*next;
}				t_token;

typedef struct s_lexer
{
	t_token		*first_token;
	int			quote; // a simple int to store info on quote input history for quotation rules
	int			token_nb; // a voir si je l'utilise en fait;
	char		*delimiter; //delimiter for << input;
	char		*std_input_redir; // this stores the standard input entered in the terminal for the 
}				t_lexer;

typedef struct s_mother
{
	char 		*line; //whole string received
	t_lexer		*lex; // pointer to the structure of tokens for input;
	char		**env; //char ** containing environment variables (useful for env and execve() PATHS)
	int			nbcmd; //number of commands
	int			pipe; //number of pipes
	int			ret;
	// int			pipes[2];
	int			redirect_mem; //an int I need to ensure compatibility between different s_command elements when redireciton is involved;
	int			exitret; // value for the exit command to be updated during execution
	char		*path; //env variable value for PATH
	t_command	*c;

	

}				t_mother;

//general
int		ft_parse(t_mother *s);
void	ft_structinit(t_mother *s);
void	ft_end(t_mother *s);
void	ft_error(t_mother *s, char * error, int code);
int		mainaftersignal(void);
void	ft_print_parsing_results(t_mother *s);
// initialization of structures
void	ft_initc(t_mother *s);
void    ft_lexinit(t_mother *s);
void	ft_structinit(t_mother *s);
void	ft_end(t_mother *s);
//builtins
int	ft_echo(t_command *c);
int		ft_cd(t_mother *s);
int		ft_pwd(t_mother *s);
int		ft_env(t_mother *s);
int 	ft_export(t_mother *s, t_command *cmd);
int 	ft_unset(t_mother *s);
int		ft_exit(t_mother *s);

//exec
int		ft_execfind(t_mother *s, t_command *c);
int	ft_execnotbuiltin(t_mother *s);
char	*ft_pathfinder(t_mother *s);

//exec with muliple commands
void	multicommands(t_mother *s);
void	ft_redirect(t_mother *s);
int		ft_pipe(t_command *c, t_mother *s);

//signaux
void	signalhandler(int c); //for ctrl-c ctrl-v

// history
void	ft_add_history(t_mother *s);
void	ft_clear_history();

//env
void	env_init(t_mother *s, char **envp);
void	create_env(t_mother *s, char *str);
void	change_env(t_mother *s, char *str, int pos);
void	add_env(t_mother *s, char *str);
void	rm_env(t_mother *s, char *str);
void	expanding_env(t_mother *s, t_token *tok);
void	quote_env_replacing(t_mother *s, t_token *tok, int start, int end);
void	env_replacing(t_mother *s, t_token *tok);
int		quote_env_finder(t_token *tok);
char	*ft_strjoin_env(char *str1, char *str2);

//env_utils
size_t	ft_strlen_array(char **array);
void	ft_free_array(char **array);
int		ft_env_cmp(char *env1, char *var);
int		ft_env_cmp_arg(char *env1, char *var);
char	*ft_return_env_value(t_mother *s, char *var, int type);

//lexer functions
void    minilexer(t_mother *s);
void    minilexer_inner_loop(t_mother *s, int *i, int *j);
t_token *create_token(t_mother *s, int i, int j, char c);
void    link_chain_elem(t_mother *s, int *i, int *j, char c);

// lexer rules extension for norm problems
void	ft_separator_rule(t_mother *s, int *i, int *j);
void	ft_new_operator_char_rule(t_mother *s, int *i, int *j);
void	ft_quote_aligner(t_mother *s, int *i, int *j);
void	ft_dollar_aligner(t_mother *s, int *i, int *j);
void	ft_delimiter(t_mother *s, int *i, int *j, int o);

//lexer utils
t_token *ft_last_elem(t_token *token);
int	    ft_match_word(char c);
void    ft_skip_word(t_mother *s, int *j);
void    quote_handler(t_mother *s, int *i, int *j);
void    dollar_tokeniser(t_mother *s, int *i, int *j);

// assign types functions
void	assign_types(t_mother *s);
void	ft_type_flag(t_token *tok);
void	ft_type_env(t_token *tok);
void	ft_type_built(t_token *tok);
void	ft_type_pipe(t_token *tok);
void	ft_type_path(t_mother *s, t_token *tok);
void	ft_type_cmd(t_mother *s, t_token *tok);

// << redirection interception for input
void	redir_input_handler(t_mother *s);
void	ft_finding_delimiter(t_mother *s, t_token *tok);
void	ft_redir_error_check(t_mother *s, t_token *tok);
void	ft_redir_input_activator(t_mother *s);
int		ft_strnstr_index(char *haystack, char *needle, int len);

// parser functions
void	miniparser(t_mother *s);
void	ft_tok_conveyor_belt(t_mother *s, t_token *tok, int *i);
void	ft_cmd_blt(t_mother *s, t_token *tok, int *i);
void	ft_add_args(t_mother *s, t_token *tok, int *i);
void	check_echo_flag(t_mother *s, t_token *tok);
void	ft_add_arg_array(t_command *last, t_token *tok);
void	ft_add_operator(t_mother *s, t_token *tok, int *i);
void	add_cmd_elem(t_mother *s, t_token *tok, int *i);
t_command	*create_cmd(t_mother *s, t_token *tok, int *i);
t_command	*ft_last_cmd(t_command *first);
void	ft_wrong_input(t_mother *s, t_token *tok, int *i);
void	assign_redirect(t_mother *s, t_token *tok, int *i);
void	pre_exec_arg_checking(t_mother *s, t_command *cmd, t_token *tok);

// memory handling for structure cleaning
void	free_t_token(t_mother *s);


#endif
