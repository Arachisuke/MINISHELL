/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:51:02 by wzeraig           #+#    #+#             */
/*   Updated: 2024/12/11 13:10:44 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	verif_dir(char **strs, t_all *all)
{
	DIR	*dir;

	if (!strs || !*strs)
		return (SUCCESS);
	if (strs[0][0] == '/' || (strs[0][0] == '.' && strs[0][1] == '/'))
	{
		dir = opendir(strs[0]);
		if (!dir)
			return (closedir(dir), ft_printf_fd(2, "minishell: %s: No such file or directory\n", strs[0],
					strerror(errno)), ft_final(all, NULL, NULL, 127));
		else
			return (closedir(dir), ft_printf_fd(2, "minishell: %s: Is a directory\n", strs[0]),
				ft_final(all, NULL, NULL, 126));
		closedir(dir);
	}
	else if (strs[0][0] == '.' && strs[0][1])
		return (ft_printf_fd(2, "minishell: %s: command not found\n", strs[0]),
			ft_final(all, NULL, NULL, 127));
	else if (strs[0][0] == '.' && !strs[0][1] && strs[1])
		return (ft_printf_fd(2, "minishell: %s: %s: file not found\n", strs[0],
				strs[1]), ft_final(all, NULL, NULL, 1));
	else if (strs[0][0] == '.' && !strs[0][1] && !strs[1])
		return (ft_printf_fd(2, "minishell: %s: filename argument required\n",strs[0]), 
		ft_printf_fd(2, "%s: usage: %s filename [arguments]\n", strs[0], strs[0]), ft_final(all, NULL, NULL, 1));
	return (SUCCESS);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	return (i);
}

int	verif_space(char *str, t_all *all)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			return (SUCCESS);
		i++;
	}
	return (ft_final(all, NULL, NULL, 1));
}

int	verif_quotes(t_all *all, char *line)
{
	int		i;
	char	quote;
	int		flag;

	quote = 0;
	flag = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == SQ || line[i] == DQ) && flag == 0)
		{
			quote = line[i];
			flag = 1;
		}
		else if ((line[i] == ' ' || is_token(line[i])) && flag == 1)
			line[i] = line[i] * -1;
		else if (line[i] == quote && flag == 1)
			flag = 0;
		i++;
	}
	if (flag == 1)
		return (ft_final(all, NULL, INVALID_SYNTAX, 1));
	return (SUCCESS);
}

int	is_double_redir(char *line, int token, int i)
{
	if (((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i
				+ 1] == '<')) && token == 0)
		return (1);
	return (0);
}

int	check_quote_and_redir(char *line, int i, int count)
{
	int	token;

	token = 0;
	while (line[i])
	{
		if (is_double_redir(line, token, i))
		{
			count++;
			i++;
		}
		else if (is_token(line[i]))
		{
			token = 0;
			count++;
		}
		i++;
	}
	return (count);
}

int	firstquotecheck(char *line, int i)
{
	if (line[i] == -34 && line[i + 1] && line[i + 1] == -34 && line[i + 2]
		&& ft_isalpha(line[i + 2]))
		return (i + 2);
	if (line[i] == -39 && line[i + 1] && line[i + 1] == -39 && line[i + 2]
		&& ft_isalpha(line[i + 2]))
		return (i + 2);
	return (i);
}
