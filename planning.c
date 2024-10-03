/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:55:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/10/03 09:41:29 by wzeraig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_line(char *str, char **garbage)
{
	// init les deux structure @@@@
	// tu regardes la liste de cmd @@@@
	// if null // if que des ispace @@@
	// quotes fermer ou pas @@@@@
	// tout mettre dans une double liste chainee et les flag @@@
	// >>>> @@@@
	// retokeniser >> dans la fonction donc prendre direct les deux
	// automate state @@@
}

void	parser_line(char *str, char **garbage, t_lexer **lexer)
// struct garbage, double pointeur pour t_lexer
{
	// recuperer la liste chainee @@@
	// regrouper les commandes entre eux [t_cmds token redirec file] @@@
	// les redirect open avec les bonnes options @@@@
 	// feuille des states @@@
	// tester mon code @@@
	// celui d'andy @@@
	// init tcmds @@@@
	// protection si la line est NULL @@@
	// is builtin @@@@
	// retokeniser >> dans la fonction donc prendre direct les deux @@@
}

void	other(char *str)
{
	// proteger les mallocs @@@@
	// expander 
	// guillemet ...
	// gerer les arguments, a voir dans liste de commande "'$shell'"
	// if une env existe pas je le met pas dans ma node
	// faire la struct garbage
	// builtin
	// les code d'exit et free garbage close struct fd
	// cas speciale : premier mot qui nest pas une commande
	// regrouper DLOWER LOWER GREATER DGREATER
}
// gerer dans sort cmds, << heredoc, dire que c un limiteur le caractere dapres...
// tester le heredoc que jai fais

// gerer dans sortcmds les expands....


// historique @@@@
// cree une structure VOIR MAIN @@@


//< in1 << in2 cat >out1 >out2 -e  >out3 >out4 -er | >  -l out4 cd -l  >out4 -l 
// verifier le com qui est dans sort_cmds @@@@



//<< lim1 < <<lim 2 || << lim3 < infile1 << lim4

// faire un malloc de fd comme ca... si ya plusieurs je les ouvre tous avec differnet int fd comme ca jai le cheminn de tous, dans l'exec je prendrais le dernier mais comme ca jai ouvert tout les fd jai ecris dedans jai juste a savoir via lexec si cest le dernier lui il va juste parcourir jusqua la fin la node redir...
// je le return dans node... depuis la fonction comme ca le retour de la fonction sers quaux erreur.. parfait



// expander regrouper les info sur les quotes, et commencer lexpand
// @ANDY fais la fonction malloc et copie des ENV et rend line tout beau tout propre.
// VERIFIER EXPAND EN L'AFFICHANT YA UN PB
//<$HOME $'HOME' '$HOME' '$'HOME "$HOME" "$""HOME" $$HOME



// faire le tour de toute les fonctions gerer les erreur si ya une erreur free, ect ect...entre chaque cmd ca free.\



// ERROR_REDIR a verifi gdb @@@@






// AUJOURDHUI 1 octobre
// verifier le quotes
// et un quotes fermer cest une chaine! un arguments
// de changer les returns et surtout dans state init.
//tester par quelquun
// builtin




// changer les returns, par l'erreur qui correspond ainsi que la fonction qui correspond.
// la fonction qui free tout, et gerer le parsing relire chaque moment et faire la bonne redirection false -> free, true ->continue
// tester le here_doc en profondeur et le expander.
// younes ou autre.
// builtin
// exec
// signaux
// lire les fonctionnalite a apoorte sur medium
// corriger les fautes!



// test echo  "ah euh ah euh" -n , -n n'est pas pris en compte comme option


// 2 octobre
// changer tout les return(0) par success// return(1) par le define correspondant
// changer apres le final enlever le retour car final return deja
// revoir la fonction ligne par ligne si tout se rejoins que ce soit au niveau des erreurs etc
// split le terminator
//tester par quelqun
//NEWNEW $? ou $variableinexistante marche pas



//TEST a gerer
// "" juste ca faut le parse, donc pas de verif dans parse_line le parser et lenvoyer a l'exec
// $variable inexistante il peut ne pas y avoir de line donc est ce que la protection serait pas utile finalement
// $?
// echo "" que mettre a l'interieur des guillemets ? si cest espace cest deja fait


// verifier chaque etape et sil faut verifier line en debut de fonction car ya des fonctions qui la change tel que get_final


// $HME
// \0 -> mallocinput ->strs ft_final free, continue
// $?
// ""
// plus besoin de faire *-1


//  < "Makefile" "<<oui'" echo "'"$HOME"'" a gerer @@@@
// < "Makefile" "<<oui'" echo "'"$HOME"'" @@@@
//<<oui'@@@
//"ok ok" "123ok" "132ok" "<<ook" "|" @@@@  



// THEME A GERER
// EXPANDEER
// QUOTES
// SAVOIR PARSER LES COMMANDE
// LES TOKENS


//faire tout les test du repertoire de commande
// gerer chaque erreur avec le bon message
// cas envoyez juste : ou ! ca ne renvoie rien car ni un token(> ou |) ni un string donc rien par contre envoyez deux fois lun de ses caractere command not found 
// yann a pas gerer il a dis direct command not found car cest une string! if pas redir donc cest une commande donc erreur!
// > gerer car le msg parle de ce quil ya apres donc si cest juste > alors dire newline sinon > | ou >>> ca va parler de pipe ou de redir