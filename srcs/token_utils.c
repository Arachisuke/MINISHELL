/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:30:40 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/05 17:17:19 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_token(t_lexer *lexer, t_all *all)
{
	if (ft_strlen(lexer->string) == 2 && is_token(lexer->string[0]))
	{
		if (lexer->string[0] == '<' && lexer->string[1] == '<')
			lexer->token = D_LOWER;
		else if (lexer->string[0] == '>' && lexer->string[1] == '>')
			lexer->token = D_GREATER;
		else if (lexer->string[0] == '<' && lexer->string[1] == '>')
			return (ft_final(all, ">", ERR_SYNTAX));
		else if (lexer->string[0] == '>' && lexer->string[1] == '<')
			return (ft_final(all, "newline", ERR_SYNTAX));
	}
	else if (lexer->string[0] == '|')
		lexer->token = PIPE;
	else if (lexer->string[0] == '>')
		lexer->token = GREATER;
	else if (lexer->string[0] == '<')
		lexer->token = LOWER;
	else
		lexer->token = STRING;
	return (0);
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_token_space(char c)
{
	return (is_token(c) || is_space(c));
}

int	is_token(char c)
{
	int		i;
	char	*token;

	token = "|><";
	i = 0;
	while (token[i])
	{
		if (token[i] == c)
			return (1);
		i++;
	}
	return (SUCCESS);
}
