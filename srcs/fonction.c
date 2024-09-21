/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:38:51 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/21 15:48:46 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**malloc_input(char *line)
{
	int		count;
	char	**strs;
	int		i;

	i = 0;
	strs = NULL;
	count = count_word(line);
	while (line[i])
	{
		if (is_token(line[i]))
			count++;
		i++;
	}
	strs = malloc(sizeof(char *) * count + 1);
	if (!strs)
		return (NULL);
	strs[count] = NULL;
	i = 0;
	return (strs);
}
void	node_affichage(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		printf("Node = %d\ncontent = %s\n token = %d\n", tmp->i, tmp->string,
			tmp->token);
		tmp = tmp->next;
		/*printf("content = %s\ncurrent = %p\n prev = %p\n next = %p\ntoken =
			%d\n",
		// 	tmp->string, tmp, tmp->prev, tmp->next, tmp->token);
		// tmp = tmp->next; */
	}
}
void	cmds_affichage(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = cmds;
	while (tmp)
	{
		printf("node = %d\nis builtin = %d\nredir_infile = %d\nredir_outfile = %d\noutfile = %s\ninfile = %s\n",
			tmp->name, tmp->is_builtin, tmp->redir_infile, tmp->redir_outfile, tmp->outfile, tmp->infile);
		while (tmp->strs[i])
		{
			printf("strs[%d] = %s\n", i, tmp->strs[i]);
			i++;
		}
		printf("\n");
		i = 0;
		tmp = tmp->next;
		/*printf("content = %s\ncurrent = %p\n prev = %p\n next = %p\ntoken =
			%d\n",
		// 	tmp->string, tmp, tmp->prev, tmp->next, tmp->token);
		// tmp = tmp->next; */
	}
}

void	init_token(t_lexer *lexer)
{
	if (ft_strlen(lexer->string) == 2 && is_token(lexer->string[0])) // 1
	{
		if (lexer->string[0] == '<' && lexer->string[1] == '<')
			lexer->token = D_LOWER;
		else if (lexer->string[0] == '>' && lexer->string[1] == '>')
			lexer->token = D_GREATER;
		else if (lexer->string[0] == '<' && lexer->string[1] == '>')
			printf("ERROR '<' '>'\n");
		else if (lexer->string[0] == '>' && lexer->string[1] == '<')
			printf("ERROR '>' '<'\n");
	}
	else if (lexer->string[0] == '|')
		lexer->token = PIPE;
	else if (lexer->string[0] == '>')
		lexer->token = GREATER;
	else if (lexer->string[0] == '<')
		lexer->token = LOWER;
	else
		lexer->token = STRING;
}