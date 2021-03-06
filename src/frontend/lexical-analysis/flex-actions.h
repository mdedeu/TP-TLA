#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"
/**
 * Se definen los diferentes IDs de cada token disponible para el scanner Flex.
 */
/*
typedef enum TokenID {

	// Por defecto, el valor "0" hace fallar el analizador sintáctico.
	UNKNOWN = 0,

	// Código de error de Bison, que permite abortar el escaneo de lexemas cuando
	// se presente un patrón desconocido. El número "257" coincide con el valor
	// que Bison le otorga por defecto, pero además permite que el resto de
	// tokens continúen desde el valor "258" lo que permite proteger los IDs
	// internos que Bison reserva para crear "tokens literales":
	YYUNDEF = 257,

	// Operadores aritméticos.
	ADD,
	SUB,
	MUL,
	DIV,

	//Operadores de comparacion
	EQ,
	LE,
	GE,
	NE,
	LT,
	GT,

	//Operadores logicos
	OR,
	AND,
	NOT,

	//Asignacion
	ASSIGN,

	// Acceso
	POINT,
	COMMA,

	// Tipos
	INT_TYPE,
	STRING_TYPE,
	
	NON_BINARY_TREE_TYPE,
	BINARY_TREE_TYPE,
	AVL_TREE_TYPE,
	RED_BLACK_TREE_TYPE,
	B_TREE_TYPE,
	BST_TREE_TYPE,
	NODE_TYPE,


	// Funciones
	MAIN,
	PRINT,
	READ,
	WRITE,
	NEW_NODE,
	DELETE_NODE,
	BALANCED,
	LENGTH,
	SIZE,
	MODIFY_NODE,
	SEARCH,
	FILTER,

	
	
	//Bloques de control
	FOR,
	WHILE,
	IF,
	ELSE,
	// Paréntesis.
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	OPEN_CURL_BRACKETS,
	CLOSE_CURL_BRACKETS,
	OPEN_SQUARE_BRACKETS,
	CLOSE_SQUARE_BRACKETS,
	QUOTE,
	SEMI_COLON,

	INTEGER,
	STRING, 
	SYMBOL
} TokenID;
*/
/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 */

yytoken_kind_t IntegerPatternAction(char * lexeme);

void IgnoredPatternAction(char * lexeme);

yytoken_kind_t UnknownPatternAction(char * lexeme);

yytoken_kind_t SymbolPatternAction(char * lexeme);

yytoken_kind_t StringPatternAction(char * lexeme);

#endif