/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:59:22 by ogenser           #+#    #+#             */
/*   Updated: 2021/10/22 15:39:35 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_mother		t_mother;
typedef struct s_command	t_command;
typedef struct s_lexer		t_lexer;
typedef struct s_token		t_token;

typedef struct s_command
{
	char		*line;
	char		*command;
	int			retvalue;
	int			cmd_status;

	int			nbarg;
	char		**arg;

	int			isfollowedbypipe;
	int			isfollowedbyche;
	int			isfollowedbydoubleche;
	t_command	*nextpipe;
	int			isprecededbypipe;
	int			isprecededbyche;
	int			isprecededbydoubleche;
	t_command	*previouspipe;

	int			isoutfile;
	char		*outfile;
	int			isinputfile;
	char		*inputfile;

	int			iserrofile;
	char		*errorfile;
	int			pipes[2];
	int			cpid;

}				t_command;

typedef struct s_token
{
	char		*token;
	char		type;
	int			pre_space;
	t_token		*prev;
	t_token		*next;
}				t_token;

typedef struct s_lexer
{
	t_token		*first_token;
	int			quote;
	int			token_nb;
	char		*delimiter;
	char		*std_input_redir;
}				t_lexer;

typedef struct s_mother
{
	char		*line;
	t_lexer		*lex;
	char		**env;
	int			nbcmd;
	int			pipe;
	int			ret;
	int			redirect_mem;
	int			exitret;
	char		*path;
	t_command	*c;
}				t_mother;

//general
pid_t		*ft_return_global_pid(void);
int			ft_parse(t_mother *s);
void		ft_structinit(t_mother *s);
void		ft_end(t_mother *s);
void		ft_error(t_mother *s, char *error, int code);
int			mainaftersignal(t_mother *s, char *str);

//mainaftersignals utils
void		exec_and_repeat(t_mother *s);
int			ft_lexer_handler(t_mother *s);
int			ft_weird_readline(t_mother *s);
void		ft_control_d(t_mother *s);
int			ft_input_is_spaces(char *str);

// initialization of structures
void		ft_initc(t_mother *s);
void		ft_lexinit(t_mother *s);
void		ft_structinit(t_mother *s);
// end of structures
void		ft_end(t_mother *s);
void		free_t_loop(t_mother *s);
void		free_t_mother(t_mother *s);
void		free_t_lexer(t_mother *s);
void		free_t_token(t_mother *s);
void		free_t_cmd(t_mother *s);
void		free_one_cmd(t_mother *s, t_command *temp);
//builtins
int			ft_echo(t_mother *s, t_command *c);
int			ft_skip_spaces(char *str, int i);
int			ft_find_equal_sign(char *str);

int			ft_cd(t_mother *s);

int			ft_pwd(t_mother *s);

int			ft_env(t_mother *s);

int			ft_export(t_mother *s, t_command *cmd);
int			ft_word_is_exportable(char *str);

int			ft_unset(t_mother *s, t_command *c);

int			ft_exit(t_mother *s, t_command *c);
int			ft_check_exit_arg(char *str);
void		ft_linking_args(t_mother *s, t_command *cmd);
int			ft_skip_quote_marks(char *str, int i, int end);
int			ft_strstr_index(char *haystack, char *needle);
int			ft_exit_arg_spaces(t_mother *s, int i, int end);
void		resolve_exit_spaces(t_command *cmd, char *built_in, int nb_args);
char		*exit_join_args_one(t_command *cmd, int *i, int *nb_args);
void		exit_join_arg_temp(char **temp, char **temp2, t_command *cmd, int *i);
void		exit_join_arg_temp2(char **temp, char **temp2, t_command *cmd, int *i);
void		exit_join_args(t_command *cmd, char *built_in, char *temp, char *temp2);

//exec
int			ft_execfind(t_mother *s, t_command *c);
int			ft_execnotbuiltin(t_mother *s, t_command *c);
char		*ft_pathfinder(t_mother *s, t_command *c);
char		*ft_pathtester(t_mother *s, t_command *c, char ***minipath,
				int minisize);
int			ft_redirect(t_command *c, t_mother *s);
void		multicommands(t_mother *s);
int			ft_pipe(t_command *c, t_mother *s);
int			ft_waitpid(t_mother *s, t_command *c, int status);

//signaux
void		signalhandler(int c); //for ctrl-c ctrl-v
void		quithandler(void);
void		quitchild(int signal);
void		killchild(int signal);

// history
void		ft_add_history(t_mother *s);
void		ft_clear_history(void);

//env
void		env_init(t_mother *s, char **envp);
void		create_env(t_mother *s, char *str);
void		change_env(t_mother *s, char *str, int pos);
void		add_env(t_mother *s, char *str);
void		rm_env(t_mother *s, char *str);
void		expanding_env(t_mother *s, t_token *tok);
void		quote_env_replacing(t_mother *s, t_token *tok, int start, int end);
void		env_replacing(t_mother *s, t_token *tok);
int			quote_env_finder(t_token *tok);
char		*ft_strjoin_env(char *str1, char *str2);

//env_utils
size_t		ft_strlen_array(char **array);
void		ft_free_array(char **array);
int			ft_env_cmp(char *env1, char *var);
int			ft_env_cmp_arg(char *env1, char *var);
char		*ft_return_env_value(t_mother *s, char *var, int type);

//lexer functions
void		minilexer(t_mother *s);
void		minilexer_inner_loop(t_mother *s, int *i, int *j);
t_token		*create_token(t_mother *s, int i, int j, char c);
void		link_chain_elem(t_mother *s, int *i, int *j, char c);

// lexer rules extension for norm problems
void		ft_separator_rule(t_mother *s, int *i, int *j);
void		ft_new_operator_char_rule(t_mother *s, int *i, int *j);
void		ft_quote_aligner(t_mother *s, int *i, int *j);
void		ft_dollar_aligner(t_mother *s, int *i, int *j);
void		ft_delimiter(t_mother *s, int *i, int *j, int o);

//lexer utils
t_token		*ft_last_elem(t_token *token);
int			ft_match_word(char c);
void		ft_skip_word(t_mother *s, int *j);
void		quote_handler(t_mother *s, int *i, int *j);
void		dollar_tokeniser(t_mother *s, int *i, int *j);

// assign types functions
void		assign_types(t_mother *s);
void		ft_type_flag(t_token *tok);
void		ft_type_env(t_token *tok);
int			ft_env_char_check(char c);
void		ft_env_tok_overflow(t_token *tok, int limiter);
void		ft_type_built(t_token *tok);
void		ft_type_pipe(t_token *tok);
void		ft_type_op(t_token *tok);
int			ft_is_op_redir(char *str);
void		ft_type_path(t_mother *s, t_token *tok);
void		ft_type_cmd(t_mother *s, t_token *tok);
int			ft_stat_check(char *path, t_token *tok);

// << redirection interception for input
void		redir_input_handler(t_mother *s);
void		ft_finding_delimiter(t_mother *s, t_token *tok);
int			ft_redir_error_check(t_mother *s, t_token *tok);
int			ft_redir_input_activator(t_mother *s);
int			ft_strnstr_index(char *haystack, char *needle, int len);

// parser functions
int			miniparser(t_mother *s);
int			ft_tok_conveyor_belt(t_mother *s, t_token *tok, int *i);
void		ft_cmd_blt(t_mother *s, t_token *tok, int *i);
int			ft_add_args(t_mother *s, t_token *tok, int *i);
void		check_echo_flag(t_mother *s, t_token *tok);
void		ft_add_arg_array(t_command *last, char *str, int type);
int			ft_add_operator(t_mother *s, t_token *tok, int *i);
void		add_cmd_elem(t_mother *s, t_token *tok, int *i);
t_command	*create_cmd(t_mother *s, t_token *tok, int *i);
t_command	*ft_last_cmd(t_command *first);
void		ft_wrong_input(t_mother *s);
void		assign_redirect(t_mother *s, t_token *tok, int *i);
void		pre_exec_arg_checking(t_mother *s, t_command *cmd, t_token *tok);

// filling c
void		fill_first_command(t_mother *s, t_token *tok);
void		plug_redir_5(t_mother *s, t_command *last);
void		fill_next_command(t_mother *s, t_command *last, t_token *tok,
				int *i);
void		input_output_checker(t_mother *s);
void		input_corrector(t_mother *s, t_command *cmd);
void		output_corrector(t_mother *s, t_command *cmd);

#endif
