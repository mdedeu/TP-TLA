#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-rules.h".
 */

yytoken_kind_t IntegerPatternAction(char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	yylval.integer = atoi(lexeme);
	return INTEGER;
}

void IgnoredPatternAction(char * lexeme) {
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

yytoken_kind_t UnknownPatternAction(char * lexeme) {
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	yylval.token = YYUNDEF;
	return YYUNDEF;
}

yytoken_kind_t SymbolPatternAction(char * lexeme) {
	LogDebug("SymbolPatternAction: '%s'.", lexeme);
	yylval.string = lexeme;
	return SYMBOL;
}

yytoken_kind_t StringPatternAction(char * lexeme) {
	LogDebug("StringPatternAction: '%s'.", lexeme);
	yylval.string = lexeme;
	return STRING;
}