/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:55:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/09/15 15:46:27 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void lexer_line(char *str, char **garbage)
{
	// init les deux structure
	// tu regardes la liste de cmd
	// if null // if que des ispace
	// quotes fermer ou pas
	// verifier les redirect >> > "< <<" verifie si ya quelque chose de vise 
	// correct pipe
	// tout mettre dans une double liste chainee et les flag
	//[t_cmds token redirec file]
	// pipe de trop ect..
}

void parser_line(char *str, char **garbage, t_lexer **lexer) // struct garbage, double pointeur pour t_lexer
{
	// recuperer la liste chainee
	// je boucle dedans et je verifie les flags
	// regrouper les commandes entre eux [t_cmds token redirec file]
	// gerer les arguments, a voir dans liste de commande "'$shell'" // savoir comment le gerer 
	// les commandes c pipex / sans pipe execve // les redirect open avec les bonnes options
}

void other(char *str)
{
	// faire une struct de fd.
	// expander
	// faire la struct garbage
	// builtin
}
