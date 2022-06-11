#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>

// Descriptor del archivo de entrada que utiliza Bison.
extern FILE * yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE * yyout;

// Variable global que contiene el número escaneado.
//extern int yylval;
// Variable global que contiene el número de la línea analizada.
extern int yylineno;

// Token actual en el tope de la pila del analizador Bison.
extern char * yytext;

// Función global de manejo de errores en Bison.
extern void yyerror(const char * string);

// Función global del analizador léxico Flex.
extern int yylex(void);

// Función global del analizador sintáctico Bison.
extern int yyparse(MainProgram program);

//Tipos de nodos
typedef struct Variable Variable;
typedef struct ParameterList ParameterList;
typedef struct Vector Vector;
typedef struct Constant Constant;
typedef struct Factor Factor;
typedef struct Expression Expression;
typedef struct For For;
typedef struct While While;
typedef struct IfClose IfClose;
typedef struct If If;
typedef struct Write Write; 
typedef struct Read Read;
typedef struct Function Function;
typedef struct Assignation Assignation;
typedef struct Declare Declare;
typedef struct DeclareAndAssign DeclareAndAssign;
typedef struct Statement Statement;
typedef struct Instruction Instruction;
typedef struct Block Block;
typedef struct MainProgram MainProgram;




// Emular tipo "boolean".
typedef enum {
	false = 0,
	true = 1
} boolean;

// Estado global de toda la aplicación.
typedef struct {

	// Indica si la compilación tuvo problemas hasta el momento:
	boolean succeed;

	// Indica el resultado de la compilación:
	int result;

	// Agregar una pila para almacenar tokens/nodos.
	// Agregar un nodo hacia la raíz del árbol de sintaxis abstracta.
	// Agregar una tabla de símbolos.
	// ...

} CompilerState;

// El estado se define e inicializa en el archivo "main.c":
extern CompilerState state;

struct MainProgram {
	Block* block;
};

typedef enum{
	INSTRUCTION_BLOCK,
	INSTRUCTION
} BlockType;

struct Block{
	BlockType * BlockType;	
	Instruction* instruction;
	Block * block;
};

typedef enum {
	STATEMENT,
	IF,
	FOR,
	WHILE
} InstructionType;

struct Instruction{
	InstructionType type;
	Statement * statement;
	If * if_instruction;;
	For * for_instruction;
	While * while_instruction;
};

typedef enum {
	DECLARE_AND_ASSIGN,
	ASSIGNATION,
	FUNCTION
} StatementType;

struct Statement{
	StatementType type;
	DeclareAndAssign * declareAndAssign;
	Assignation * assignation;
	Function * function;
};

typedef enum {
	DECLARE_ASSIGN_EXPRESSION,
	DECLARE_ASSIGN_PARAM_LIST,
	DECLARE
} DeclareAndAssignType;

struct DeclareAndAssign {
	DeclareAndAssignType * type;
	Declare * declare;
	Expression * expression;
	ParameterList * parameterList;
};

typedef enum{
	TYPE_SYMBOL,
	TREE_TYPE_SYMBOL,
	TYPE_VECTOR
} DeclareType;

struct  Declare{
	int type;
	int type_token;
	int treeType_token;
	Vector * vector;
	char * variable;
};

struct Assignation {
	char * variable;
	Expression* Expression;
};

typedef enum {
	NO_PARAM_FUNCTIONS,
	ONE_PARAM_FUNCTIONS,
	MULTI_PARAM_FUNCTIONS,
	FILTER_FUNCTION,
	READ_FUNCTION,
	WRITE_FUNCTION
} FunctionType;

struct Function {
	FunctionType type;
	char * variable;
	int noParamFunctionToken;
	int oneParamFunctionToken;
	Expression * expression;
	int multiParamFunctionToken;
	ParameterList * parameterList;
	Read * read;
	Write * write;
};

struct Read{
	char * variable;
};

struct Write {
	Expression * expression;
};

typedef enum {
	IF_CLOSE_NORMAL,
	IF_ELSE
}IfCloseType;

struct  IfClose{
	Block* block;
	IfCloseType * ifCloseType;
};

struct If {
	Expression* expression;
	Block * block;
	IfClose * ifClose;
};

struct While {
	Expression * expression;
	Block * block;
};

typedef enum {
	DECLARE_ASSIGN_FOR,
	ASSIGNATION_FOR,
	INCOMPLETE_FOR
} ForType;

struct For {
	ForType type;
	DeclareAndAssign * declareAndAssign;
	Assignation * assignation;
	Expression * expression;
	Statement * statement;
	Block * block;
};
//----------------------------------------------
typedef enum {
	ADD_EXPRESSION,
	SUB_EXPRESSION,
	MUL_EXPRESSION,
	DIV_EXPRESSION,
	FACTOR_EXPRESSION,
	GT_EXPRESSION,
	GE_EXPRESSION,
	LE_EXPRESSION,
	LT_EXPRESSION,
	NE_EXPRESSION,
	NE_EXPRESSION,
	EQ_EXPRESSION,
	NOT_EXPRESSION,
	FUNCTION_EXPRESSION,
	VECTOR_EXPRESSION
} ExpressionType;

struct Expression {
	ExpressionType type;
	Expression * left;
	Expression * right;
	Factor * factor;
	Function * function;
	Vector* vector;
};

typedef enum {
	CONSTANT_FACTOR,
	STRING_FACTOR,
	SYMBOL_FACTOR,
	EXPRESSION_FACTOR
} FactorType;

struct Factor {
	FactorType type;
	Constant * constant;
	char * string;
	char * variable;
	Expression * expression;
};

struct Constant {
	int value;
};

typedef enum {
	CONSTANT_VECTOR,
	SYMBOL_VECTOR
} VectorType;

struct Vector {
	VectorType type;
	char * variable;
	Constant * constant;
	char * variable2;
};

typedef enum {
	EXPRESSION,
	PARAM_COMMA_EXPRESSION
} ParameterListType;

struct ParameterList {
	ParameterListType type;
	Expression * expression;
	ParameterList * parameterList;
};

/*
struct Variable{
	char * name;
	void * value;
	int type;
};
*/

#endif
