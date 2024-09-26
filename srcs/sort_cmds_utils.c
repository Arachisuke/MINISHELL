/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:25:10 by ankammer          #+#    #+#             */
/*   Updated: 2024/09/26 13:30:03 by ankammer         ###   ########.fr       */
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

char	*free_nodes(t_simple_cmds *cmds)
{
	t_simple_cmds	*curr;

	if (!cmds)
		return (NULL);
	curr = cmds;
	while (cmds)
	{
		if (cmds->strs)
			ft_free(cmds->strs);
		if (cmds->redir)
			free(cmds->redir);
		curr = cmds->next;
		free(cmds);
		cmds = NULL;
		cmds = curr;
	}
	return (NULL);
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

