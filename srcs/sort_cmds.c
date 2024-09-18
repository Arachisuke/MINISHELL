/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:25:10 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/18 18:01:18 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_builtin(char *str)
{
	if (ft_strncmp(str, "cd", 2))
		return (1);
	else if (ft_strncmp(str, "echo", 4))
		return (1);
	else if (ft_strncmp(str, "env", 4))
		return (1);
	else if (ft_strncmp(str, "exit", 4))
		return (1);
	else if (ft_strncmp(str, "export", 6))
		return (1);
	else if (ft_strncmp(str, "pwd", 3))
		return (1);
	else if (ft_strncmp(str, "unset", 5))
		return (1);
	return (0);
}

t_simple_cmds	*malloc_cmds_struct(t_lexer *current)
{
	int				nb_pipe;
	t_simple_cmds	*cmds;

	nb_pipe = 0;
	cmds = NULL;
	while (current)
	{
		if (current->token == PIPE)
			nb_pipe++;
		current = current->next;
	}
	create_node_cmds(&cmds, nb_pipe);
	if (!cmds)
		return (NULL);
	return (cmds);
}

t_simple_cmds	*sort_cmds(t_lexer *lexer)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*cmds_tmp;
	t_lexer			*current;
	char			*tmp;

	current = lexer;
	cmds = malloc_cmds_struct(current);
	cmds_tmp = cmds;
	cmds_tmp->redirections = malloc(sizeof(t_lexer) * 1);
	while (current)
	{
		if (current->token != PIPE)
		{
			if (current->token == GREATER || current->token == D_GREATER
				|| current->token == LOWER || current->token == D_LOWER)
			{
				cmds_tmp->redirections->token = current->token;
				if (current->next->token == STRING)
				{
					cmds_tmp->hd_file_name = current->next->string;
					current = current->next;
				}
				// else
				// 	return(printf("expected file after redirection,free_malloc 1);
			}
			else if (current->token == STRING)
			{
				tmp = ft_strdup(current->string);
				if (is_builtin(current->string))
					cmds_tmp->is_builtin = 1;
				while (current->token == STRING)
				{
					if (current->next->token != STRING)
						break ;
					tmp = ft_strjoin(tmp, current->next->string);
					cmds_tmp->str = ft_split(tmp, ' ');
					current = current->next;
					free(tmp);
				}
			}
		}
		else
		{
			cmds_tmp = cmds_tmp->next;
			cmds_tmp->redirections = malloc(sizeof(t_lexer) * 1);
		}
		current = current->next;
	}
	if (tmp)
		free(tmp);
	return (cmds);
}
