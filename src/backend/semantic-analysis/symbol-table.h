#ifndef SYMBOL_TABLE_HEADER
#define SYMBOL_TABLE_HEADER

#include "../support/khash.h"
#include "../support/shared.h"
struct Variable{
	Token * type;
	char * name;

    union {
        int nodes;
        int intValue;
        char * stringValue;
        ParameterList * parameterList;
    } value;
    
};

void init_symbol_table(void);

void free_symbol_table(void);

Variable* symbol_table_put(char* name, Token* type);

boolean symbol_table_exists(char* name);

Variable* symbol_table_get(char* name);

#endif