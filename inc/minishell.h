/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:21:34 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/19 11:07:58 by wzeraig          ###   ########.fr       */
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
typedef struct s_simple_cmds
{
	int						name;
	char					**strs;
	char					*str;
	// int						(*builtin)(t_tools *, struct s_simple_cmds *);
	bool					is_builtin;
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}							t_simple_cmds;

int							is_space(char c);
char						**malloc_input(char *line);
int							is_token(char c);
int							all_verifs(char *line);
t_simple_cmds				*sort_cmds(t_lexer *lexer);
t_simple_cmds				*malloc_cmds_struct(t_lexer *current);
bool						is_builtin(char *str);
t_simple_cmds				*create_node_cmds(t_simple_cmds **cmds,
								int nb_pipe);
t_simple_cmds				*ft_new_cmds(int i);

int							is_token_space(char c);
int							count_word(const char *str);
char						*remplir(char *line, int start, int end);
char						*tokenisation(char *line, int *index, int *j);
char	**parse_line(char *line, char **strs); // a tester
t_lexer						*create_node(t_lexer **lexer, char **strs);
t_lexer						*ft_new(void *content, int i);
void						ft_back(t_lexer **lst, t_lexer *new);
t_lexer						*ft_last(t_lexer *lst);
int							ft_size(t_lexer *lst);
char						*get_current_dir(void);
void						node_affichage(t_lexer *lexer);
char						*verif_space(char *line);
char						*verif_quotes(char *line);
void						init_token(t_lexer *lexer);
int							state_init(t_lexer *stack);
int							state_string(t_lexer *stack);
int							state_pipe(t_lexer *stack);
int							state_redirection(t_lexer *stack);
void						cmds_affichage(t_simple_cmds *cmds);

#endif