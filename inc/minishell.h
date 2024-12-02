/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:21:34 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/02 15:57:13 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define SQ '\''
# define DQ '\"'
# define IS_BUILTIN 1
# define SUCCESS 0
# define ERR_INVALID_INPUT "syntax error : line"
# define ERR_FILL_LINE 3
# define ERR_SYNTAX "minishell : syntax error near unexpected token: `"
# define ERR_FD "failed to open file descriptor"
# define ERR_READ 6
# define ERR_ENV "error env"
# define ERR_LINE "error line"
# define INVALID_SYNTAX "minishell: Invalid syntax: unclosed quotes"
# define ERR_EGAL "minishell: export: `"
# define ERR_OPEN_DIR 11
# define ERR_BASE "minishell : "
# define ERR_OPT "export: bad option: "

extern int					g_sig;

typedef struct s_parse
{
	int						i;
	int						j;
	int						flag;
	int						start;
	int						end;
	char					quotes;
}							t_parse;

typedef enum e_token
{
	STRING,
	PIPE,
	LOWER,
	D_LOWER,
	GREATER,
	D_GREATER,
}							t_token;

typedef struct s_lexer
{
	int						i;
	t_token					token;
	char					*string;
	struct s_lexer			*next;
	struct s_lexer			*prev;
}							t_lexer;
typedef struct s_expand
{
	int						i;
	int						lenbefore;
	int						lenafter;
	int						is_file;
	char					*strtoexpand;
	char					*strexpanded;
	struct s_expand			*next;

}							t_expand;

typedef struct s_redir
{
	char					*file_name;
	t_token					token;
	int						fd_here_doc;
	int						ifhdoc;
	struct s_redir			*next;

}							t_redir;

typedef struct s_simple_cmds
{
	int						index;
	char					**strs;
	bool					is_builtin;
	int						num_redirections;
	int fd_outfile; // rajout de fd pour infile et outfile
	int						fd_infile;
	t_redir					*redir;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}							t_simple_cmds;

typedef struct s_my_env
{
	char					*key;
	char					*value;
	int						index;
	struct s_my_env			*next;
}							t_my_env;
typedef struct s_pipex
{
	t_simple_cmds			*cmds;
	int						**pipefd;
	pid_t					*pid;
	int						status;
	char					**all_path;
	char					*path;
	int						nbrcmd;
	t_redir					*last_outfile;
	t_redir					*last_infile;
	char					**env;

}							t_pipex;

typedef struct s_all
{
	t_lexer					*lexer;
	t_lexer					*tmp_lexer;
	t_simple_cmds			*cmds;
	t_simple_cmds			*tmp_cmds;
	char					*line;
	char					**strs;
	t_expand				*expand;
	int						tab[100];
	int						id;
	char					*shell_id;
	t_my_env				*my_env;
	t_pipex					*pipex;
	int						exit_code;
}							t_all;

t_simple_cmds				*malloc_cmds_struct(t_lexer *current);
int							malloc_input(t_all *all);
int							malloc_final_line(char **line, int len_total,
								char **line_tmp);
int							is_space(char c);
int							is_token(char c);
bool						is_builtin(char *str);
char						**get_env(char **envp);
t_simple_cmds				*create_node_cmds(t_simple_cmds **cmds,
								int nb_pipe);
int							expandornot(t_all *all);
t_simple_cmds				*ft_new_cmds(int i);
char						*strjoinfree(char const *s1, char const *s2);
int							sort_cmds(t_all *all);
t_expand					*ft_back_expand(t_expand **lst, t_expand *new);
t_expand					*ft_new_expand(void);
int							is_token_space(char c);
int							count_word(const char *str);
char						*remplir(t_all *all, int start, int end);
int							checktab(int *tab, int j);
char						*tokenisation(char *line, int **index);
char						**parse_line(t_all *all, char **strs,
								t_parse *parse);
t_lexer						*create_node(t_all *all, t_lexer **lexer,
								char ***strs);
t_lexer						*ft_new(t_all *all, void *content, int i);
void						ft_back(t_lexer **lst, t_lexer *new);
t_lexer						*ft_last(t_lexer *lst);
int							ft_size(t_lexer *lst);
int							if_here_doc(t_all *all);
void						get_current_dir(char **line);
void						node_affichage(t_lexer *lexer);
int							verif_quotes(t_all *all, char *line);
int							verif_space(char *line, t_all *all);

int							init_token(t_lexer *lexer, t_all *all);
int							state_init(t_lexer *stack, t_all *all);
int							state_string(t_lexer *stack, t_all *all);
int							state_pipe(t_lexer *stack, t_all *all);
int							state_redirection(t_lexer *stack, t_all *all);
void						cmds_affichage(t_simple_cmds *cmds);
char						**malloc_strs(int arg_count);
char						*free_cmds(t_simple_cmds **cmds);
void						free_strs(char **strs);
void						ft_back_redir(t_redir **lst, t_redir *new);
t_redir						*ft_new_redir(void);
t_redir						*ft_last_redir(t_redir *lst);
int							get_final_line(t_all *all);
t_expand					*create_nodexpand(t_expand **expand, int nbrexpand);
void						expand_affichage(t_expand *expand);
int							find_var(t_all *all);
int							find_var(t_all *all);
int							init_all(t_all *all, char **envp, t_pipex *pipex);

int							checkredir(char *line, int i);
char						*free_redir(t_simple_cmds *cmds);
char						*free_lexer(t_lexer **lexer);
char	*free_expand(t_expand **expand); // 4
int							ft_final(t_all *all, char *error, char *msgerror,
								int sortie);

int							count_word_quotes(const char *str, int *i);
int							skip_spaces(char *str);
int							check_quote_and_redir(char *line, int i, int count);
int							is_double_redir(char *line, int token, int i);
void						fill_tab(int indice, int *tab, int **k);
void						init_parse(t_parse *parse, char *line);
int							count_arg(t_lexer *curr);
int							firstquotecheck(char *line, int i);
char						*ft_pid(t_all *all, t_expand **tmp);
t_my_env					*ft_myenv(t_all *all, char **envp);
t_my_env					*create_node_env(t_my_env **my_env, int i);
int							is_negative_quotes(char c);
int							is_closed_quotes(char *line, t_parse **parse,
								char **strs);
int							quotes_is_beginning(int *flag);
void						builtins_or_not(t_all *all, t_simple_cmds *cmds);
void						ft_cd(t_simple_cmds *cmds, t_all *all);
int							ft_echo(char **args);
void						ft_env(t_my_env *my_env);
int							ft_exit(t_simple_cmds *cmds, t_all *all);
void						ft_export(t_all *all, char **strs);
void						ft_pwd(t_simple_cmds *cmds);
void						ft_unset(t_all *all, char **strs);

void						msg_error(t_all *all, char *msgerror, char *error);
t_my_env					*modify_env(char *key, char *value, t_my_env *env);
t_my_env					*ft_last_env(t_my_env *my_env);
void						free_all(t_all *all);
char						*removequotes(char *line);
char	*free_env(t_my_env **env); // 3 ou 1
int							ft_pipex(t_all *all, t_pipex *pipex,
								t_simple_cmds *cmds, t_my_env *envp);

int							init_struct(t_all *all, t_pipex *pipex,
								t_simple_cmds *cmds);

void						close_fd(t_pipex *pipex, t_simple_cmds *cmds);

char						*checkcmd(t_all *all, char **all_path, char *cmd,
								t_pipex *pipex);
void						free_tab(int **tab, t_pipex *pipex);
int							wait_childs(pid_t pid, t_pipex *data);
int							init_variable(t_pipex *pipex, t_all *all);
int							open_and_close(t_all *all, t_simple_cmds *cmds,
								t_pipex *pipex);

int							process_final(t_all *all, t_pipex *pipex);
int							first_process(t_all *all, t_pipex *pipex,
								t_simple_cmds *cmds);
void						parsing_pipex(t_pipex *pipex, char **envp);
int							process_middle(t_all *all, t_simple_cmds *cmds,
								int i);
char						*strjoinfrees2(char const *s1, char const *s2);

char						*strjoinegal(char const *s1, char const *s2);
int							envlist_envchar(t_pipex *pipex, t_my_env *envp);
int							create_process(t_all *all, t_pipex *pipex);
int							ft_lstsize_env(t_my_env *lst);
int							ft_size_cmds(t_simple_cmds *lst);
int							onecmd(t_all *all, t_pipex *pipex,
								t_simple_cmds *cmds);
int							ft_errparent(t_all *all, char *str, t_pipex *pipex,
								int msg);
int							ft_errchild(t_all *all, char *str, t_pipex *pipex,
								int msg);
void						ft_signals(void);
bool						catchsignals(t_all *all);

#endif