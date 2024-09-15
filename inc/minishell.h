/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:21:34 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/15 13:52:36 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef enum e_token
{
	STRING,
	PIPE,
	GREATER,
	LOWER,
	D_GREATER,
	D_LOWER,
}					t_token;

typedef struct s_lexer
{
	int				i;
	t_token			token;
	char			*string;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

#endif