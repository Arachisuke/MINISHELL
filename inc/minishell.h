/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:21:34 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/10 12:46:27 by ankammer         ###   ########.fr       */
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
# define ERR_MALLOC 1
# define ERR_INVALID_INPUT 2
# define ERR_FILL_LINE 3
# define ERR_SYNTAX 4
# define ERR_FD 5
# define ERR_READ 6
# define ERR_ENV 7
# define ERR_LINE 8
# define INVALID_SYNTAX 9

typedef struct s_parse
{
	int						i;
	int						j;
	int						flag;
	int						start;
	int						end;
}							t_parse;

typedef enum e_token
{
	STRING,
	PIPE,
	GREATER,
	LOWER,
	D_GREATER,
	D_LOWER,
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
	struct s_redir			*next;
	int						HD;

}							t_redir;

typedef struct s_simple_cmds
{
	int						name;
	char					**strs;
	bool					is_builtin;
	int						num_redirections;
	t_redir					*redir;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}							t_simple_cmds;

typedef struct s_all
{
	t_lexer					*lexer;
	t_lexer *tmp_lexer; // cest des copies donc pas de free
	t_simple_cmds			*cmds;
	t_simple_cmds *tmp_cmds; // la aussi
	char					*line;
	char					**strs;
	t_expand				*expand;
	char					**envp;
	int						tab[100];
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
char						*tokenisation(char **strs, char *line, int *index,
								int *j);
char						**parse_line(t_all *all, char **strs,
								t_parse *parse);
t_lexer						*create_node(t_all *all, t_lexer **lexer,
								char ***strs);
t_lexer						*ft_new(t_all *all, void *content, int i);
void						ft_back(t_lexer **lst, t_lexer *new);
t_lexer						*ft_last(t_lexer *lst);
int							ft_size(t_lexer *lst);
int							if_here_doc(t_all *all);
char						*get_current_dir(void);
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
int							find_var(t_all *all, char **envp);
int							init_all(t_all *all, char **envp);
char						*negative_hollow(char *s);
int							checkredir(char *line, int i);
char						*free_redir(t_redir **redir);
char						*free_lexer(t_lexer **lexer);
char						*free_expand(t_expand **expand);
int							ft_final(t_all *all, char *error, int sortie);
int							count_word_quotes(const char *str, int i,
								int *compteur);
int							skip_spaces(char *str);
int							check_quote_and_redir(char *line, int i, int count);
int							is_double_redir(char *line, int token);
void						fill_tab(int indice, int *tab, int **k);
void							init_parse(t_parse *parse, char *line);
int							count_arg(t_lexer *curr);

#endif