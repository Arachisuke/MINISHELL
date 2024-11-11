/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:25:10 by ankammer          #+#    #+#             */
/*   Updated: 2024/11/11 15:07:45 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_builtin(char *str)
{
	if (!ft_strncmp(str, "cd", 2) && ft_strlen(str) == 2)
		return (IS_BUILTIN);
	else if (!ft_strncmp(str, "echo", 4) && ft_strlen(str) == 4)
		return (IS_BUILTIN);
	else if (!ft_strncmp(str, "env", 3) && ft_strlen(str) == 3)
		return (IS_BUILTIN);
	else if (!ft_strncmp(str, "exit", 4) && ft_strlen(str) == 4)
		return (IS_BUILTIN);
	else if (!ft_strncmp(str, "export", 6) && ft_strlen(str) == 6)
		return (IS_BUILTIN);
	else if (!ft_strncmp(str, "pwd", 3) && ft_strlen(str) == 3)
		return (IS_BUILTIN);
	else if (!ft_strncmp(str, "unset", 5) && ft_strlen(str) == 5)
		return (IS_BUILTIN);
	return (SUCCESS);
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
	s = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s == NULL)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	free((char *)s2);
	return (s);
}
