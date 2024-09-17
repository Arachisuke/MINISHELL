/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:38:51 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/17 13:56:20 by wzeraig          ###   ########.fr       */
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
	strs[count] = NULL;
	i = 0;
	if (!strs)
		return (NULL);
	return (strs);
}
void	node_affichage(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		printf("content = %s\ncurrent = %p\n prev = %p\n next = %p\ntoken = %d\n",
			tmp->string, tmp, tmp->prev, tmp->next, tmp->token);
		tmp = tmp->next;
	}
}

void	init_token(t_lexer *lexer)
{
	if (lexer->string[0] == '|')
		lexer->token = PIPE;
	else if (lexer->string[0] == '>')
		lexer->token = GREATER;

	else if (lexer->string[0] == '<')
		lexer->token = LOWER;
	else
		lexer->token = STRING;
}