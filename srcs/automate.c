/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:42:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/27 11:59:08 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	state_init(t_lexer *stack, t_all *all)
{
	t_lexer	*tmp;

	if (!all->line || !stack)
		return (ft_final(all, NULL, NULL, 1));
	tmp = stack;
	if (stack->token == STRING)
	{
		if (state_string(tmp, all))
			return (1);
	}
	else if (stack->token == D_GREATER || stack->token == D_LOWER
		|| stack->token == LOWER || stack->token == GREATER)
	{
		if (state_redirection(tmp, all))
			return (1);
	}
	else
		return (ft_final(all, stack->string, ERR_SYNTAX, 1));
	return (SUCCESS);
}

int	state_string(t_lexer *stack, t_all *all)
{
	if (stack->next)
		stack = stack->next;
	else
		return (SUCCESS);
	if (stack->token == STRING)
	{
		if (state_string(stack, all))
			return (1);
	}
	else if (stack->token == D_GREATER || stack->token == D_LOWER
		|| stack->token == LOWER || stack->token == GREATER)
	{
		if (state_redirection(stack, all))
			return (1);
	}
	else if (stack->token == PIPE)
	{
		if (state_pipe(stack, all))
			return (1);
	}
	else
		return (ft_final(all, stack->string, ERR_SYNTAX, 1));
	return (SUCCESS);
}

int	state_pipe(t_lexer *stack, t_all *all)
{
	if (stack->next)
		stack = stack->next;
	else
		return (ft_final(all, stack->string, ERR_SYNTAX, 1));
	if (stack->token == STRING)
	{
		if (state_string(stack, all))
			return (1);
	}
	else if (stack->token == D_GREATER || stack->token == D_LOWER
		|| stack->token == LOWER || stack->token == GREATER)
	{
		if (state_redirection(stack, all))
			return (1);
	}
	else
		return (ft_final(all, stack->string, ERR_SYNTAX, 1));
	return (SUCCESS);
}

int	state_redirection(t_lexer *stack, t_all *all)
{
	if (stack->next)
		stack = stack->next;
	else
		return (ft_final(all, "newline", ERR_SYNTAX, 1));
	if (stack->token == STRING)
	{
		if (state_string(stack, all))
			return (1);
	}
	else
		return (ft_final(all, stack->string, ERR_SYNTAX, 1));
	return (SUCCESS);
}
