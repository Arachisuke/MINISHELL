/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzeraig <wzeraig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:55:41 by wzeraig           #+#    #+#             */
/*   Updated: 2024/11/11 15:52:13 by wzeraig          ###   ########.fr       */
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
//echo "'l'" > '"lo"'



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


// TESTER
// $USER_
// double dollar ??
// sil ya un pipe ca ne marchait pas ...le probleme de l'incrementation de J....
// reregler ""ls (marche) a "" ls (cmd not found)





// OCTOBRE 13!

// le *-1 des quotes ne sers a rien!
// valgrind $ nombre impair
//valgrind // echo "$HOME:$=" // echo $: @@@@@
//mettre plein de commande et ensuite exit et/ou mettre juste un caratere @@@
// tester $$HOME si home est bien expand @@@
//tester $$$HOME @@@
// erreur $$HOME$HOME @@@@
// valgrind tout les test au dessus en plus de ceux repertorier sur le googlesheet
// makefile le minishell.a et minishell ne se supp pas a verifier
// supp les fonctions negative hollow et double dollar et chercher els fonctions inutiliser @@@
// tester avec guillemet les token et sans guillemet mettre des redir des pipe ect, et mettre des vrai sans guillemet tjr regarde si count vaut bien le count et lentotal et bon!
//verifier si cest vraiment le pid du shell le $$ et pas celui dun prog
//verifier si ont doit utiliser toute les fonctions proposer..
//strerror est interessant pour les msg derreur avec errno
//si un expand existe pas error chez yan et si ya echo > $HOE il dit que c une erreur alors que dans bash ca affiche juste rien // nous c boon
//supp syntax error line
//doit on supp lhistorique ?



// 14 octobre
// je fais unset et export andy exit et cd
// on verifie bien les bultins sils sont correct
// balancer le pipex // plus sortie d'erreur
// balancer les signaux
// faire full test avec valgrind
// rajoute les messages d'erreur de CHAQUE BULTINS et NOUVELLE FONCTIONS 
// chaque fonction rajouter, bien free les valeurs et mettre NUL au copie de valeur et bien renvoyez le bon msg
// changer toutes les fonctions qui depend de env car env est devenu une liste chaine @@@@@

// faire node de env@@
// faire export avec cmds au lieu de line c'est plus simple.








// 5 NOVEMBRE
// verifier export avec gdb et toutiquenti
// finir export unset et poser pipex AUJOURDHUI
// ensuite finir par tout tester.



 // 6 NOV
// paufiner le msgerror, et remettre tout le code a jour avec cette fonction. @@@@@@@@@@
// verifier les cas d'erreur de export @@@@@@
// verifier unset par rapport au index de env, jai deja mis un printf pour verifier lavant et apres changement@@@@@@@@@




// cas d'erreur de unset... juste la cmd doit etre bien ortographier c tout @@@@
//export plusieurs variable en meme temps @@@@@
// si le premier unset existe pas ou le premier export nexiste pas est ce que ceux dapres qui existe marche @@@@
// le cas chiffre espace chiffre -> erreur et on intialise la variable @@@
// si la cmd est mauvaise c pipex qui gere @@@@





// changer la methode pour recuperer env et value car maintenant cest line
// DERNIERE VERIF CAS D'ERREUR EXPORT UNSET
// entre quotes pas d'espace.


// echo 
// all my env faut le free apres la boucle vu quon en a besoin pendant toute lexecution!@@@@@@
// rechercher tout les malloc et les sorties d'erreur et gerer en faisant des free et des vrai sortie et msg
// regler et revoir tout les builtins et cas d'errreur builtin
// lire le main tres lentement...valgrind et entre fonction reaction en chaine.
// 



// a quoi sers la sortie de ft_final
// reduire export et les autres fonction a 25
// PIPEX
// test avec l'ecran split 
// printf count, line, et cmds.->







// pourquoi quand ya une guillemet on dis que cest un autre mot.
// unclosed quotes sa segfault @@@@@
// revenir a mon ancien export et le retester.


//9 NOV

// finir parse_line ce quil ya sur ton livre, et remettre lancien export


//lancien raisonnement de notre parse line cetait que quand yavais une commande comme echo "" on pensait quil comprennais espace, mais il comprennait que cetait vide, y avais les deux cas je les avait repetorier