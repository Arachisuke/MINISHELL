/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:42:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/29 16:15:16 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	state_init(t_lexer *stack)
{
	t_lexer	*tmp;

	tmp = stack;
	if (stack->token == STRING)
		state_string(tmp);
	else if (stack->token == D_GREATER || stack->token == D_LOWER
		|| stack->token == LOWER || stack->token == GREATER)
		state_redirection(tmp);
	else
		return (printf("ERROR_init\n"));
	return (0);
}
int	state_string(t_lexer *stack)
{
	if (stack->next)
		stack = stack->next;
	else
		return (0);
	if (stack->token == STRING)
		state_string(stack);
	else if (stack->token == D_GREATER || stack->token == D_LOWER
		|| stack->token == LOWER || stack->token == GREATER)
		state_redirection(stack);
	else if (stack->token == PIPE)
		state_pipe(stack);
	else
		return (printf("ERROR_string\n"));
	return (0);
}

int	state_pipe(t_lexer *stack)
{
	if (stack->next)
		stack = stack->next;
	else
		return (printf("ERROR_pipe\n"));
	if (stack->token == STRING)
		state_string(stack);
	else if (stack->token == D_GREATER || stack->token == D_LOWER
		|| stack->token == LOWER || stack->token == GREATER)
		state_redirection(stack);
	else
		return (printf("ERROR_pipe\n"));
	return (0);
}
int	state_redirection(t_lexer *stack)
{
	if (stack->next)
		stack = stack->next;
	else
		return (printf("ERROR_redir\n"));
	if (stack->token == STRING)
		state_string(stack);
	else
		return (printf("ERROR_redir\n"));
	return (0);
}
