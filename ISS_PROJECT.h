#ifndef _ISS_PROJECT_H
#define _ISS_PROJECT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>

#define NB_REGS 32	/*!< Nombre de registres */
#define SIZE_MEM 1024	/*!< Taille maximale de la mémoire*/

typedef enum
{
	STOP,	/*!< Arrêt de la machine. */
	ADD,	/*!< Addition entière. */
	SUB,	/*!< Soustraction entière. */
	MULT,	/*!< Multiplication entière. */
	DIV,	/*!< Quotient entier. */
	AND,	/*!< "ET" bit à bit. */
	OR,	/*!< "OU" bit à bit. */
	XOR,	/*!< "OU EXCLUSIF" bit à bit. */
	SHL,	/*!< Décalage arithmétique logique à gauche. */
	SHR,	/*!< Décalage arithmétique logique à droite. */
	SLT,	/*!< Test "INFERIEUR". */
	SLE,	/*!< Test "INFERIEUR OU EGAL". */
	SEQ,	/*!< Test "EGAL". */
	LOAD,	/*!< Lecture mémoire. */
	STORE,	/*!< Ecriture mémoire. */
	JMP,	/*!< Branchement. */
	BRAZ,	/*!< Branchement si zéro. */
	BRANZ,	/*!< Branchement si pas zéro. */
	SCALL,	/*!< Appel système. */
} Commande;

int init();
int fetch();
void decode(uint32_t instr);
void eval();
void showRegs();
void run();

/**
 *	\brief	Lit le contenu d'un fichier et l'exporte dans une chaine de caractère
 *	\param	filePath	Nom du fichier à lire
 *	\param	fileContent	Contenu du fichier lu
 *	\return	
 */
int	readFile(char* filePath, char** fileContent);

/**
 *	\brief	Compte le nombre de lignes présentes dans une chaine de caractère
 *	\param	string	Chaine de caractère à analyser
 *	\return	Nombre de lignes présentes dans la chaine
 */
int howManyLines(char* string);

/**
 *	\brief	Découpe une chaine de caractère en un tableau de lignes
 *	\param	string	Chaine de caractère à découper
 *	\param	lines	Tableau de chaine de caractères résultant de l'opération de déocupage
 *	\return	Nombre de lignes présentes dans la chaine originale
 */
int stringToLines(char* string, char* lines[]);

/**
 *	\brief	Compare un caractère à plusieurs caractères sous forme de tableau
 *	\param	c	Caractère à comparer
 *	\param	cmpTabChar	Tableau de caractères
 */
bool cmpChar(char c, char* cmpTabChar);
#endif
