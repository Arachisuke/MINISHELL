/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:25:10 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/19 12:03:23 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", 2) && ft_strlen(str) == 2)
		return (1);
	else if (!ft_strncmp(str, "echo", 4) && ft_strlen(str) == 4)
		return (1);
	else if (!ft_strncmp(str, "env", 4) && ft_strlen(str) == 4)
		return (1);
	else if (!ft_strncmp(str, "exit", 4) && ft_strlen(str) == 4)
		return (1);
	else if (!ft_strncmp(str, "export", 6) && ft_strlen(str) == 6)
		return (1);
	else if (!ft_strncmp(str, "pwd", 3) && ft_strlen(str) == 3)
		return (1);
	else if (!ft_strncmp(str, "unset", 5) && ft_strlen(str) == 5)
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
char	*strjoinfree(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (NULL);
	j = 0;
	i = 0;
	s = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2));
	if (s == NULL)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i++] = ' ';
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	free((char *)s1);
	return (s);
}

void	init_redirection(t_lexer *redirection)
{
	if (redirection)
	{
		redirection->i = 0;
		redirection->string = NULL;
		redirection->next = NULL;
		redirection->prev = NULL;
		redirection->token = 0;
	}
}

t_simple_cmds	*sort_cmds(t_lexer *lexer)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*tmp;
	t_lexer			*curr;

	curr = lexer;
	cmds = malloc_cmds_struct(curr);
	tmp = cmds;
	tmp->redirections = malloc(sizeof(t_lexer) * 1);
	init_redirection(tmp->redirections);
	while (curr)
	{
		if (curr->token != PIPE)
		{
			if (curr->token == GREATER || curr->token == D_GREATER
				|| curr->token == LOWER || curr->token == D_LOWER)
			{
				tmp->redirections->token = curr->token;
				if (curr->next->token == STRING)
				{
					tmp->hd_file_name = curr->next->string;
					curr = curr->next;
				}
			}
			else if (curr->token == STRING)
			{
				tmp->str = ft_strdup(curr->string);
				if (is_builtin(curr->string))
					tmp->is_builtin = 1;
				while (curr->token == STRING && curr->next && curr->next->token == STRING)
				{
					if (curr->next->token != STRING)
						break ;
					tmp->str = strjoinfree(tmp->str, curr->next->string);
					tmp->strs = ft_split(tmp->str, ' ');
					curr = curr->next;
					free(tmp->str);
				}
			}
		}
		else
		{
			tmp = tmp->next;
			tmp->redirections = malloc(sizeof(t_lexer) * 1);
		}
		curr = curr->next;
	}
	return (cmds);
}
