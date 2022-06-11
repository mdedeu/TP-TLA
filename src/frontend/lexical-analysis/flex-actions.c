#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-rules.h".
 */

TokenID IntegerPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	yylval.integer = atoi(lexeme);
	yylval.token = INTEGER;
	return INTEGER;
}

void IgnoredPatternAction(const char * lexeme) {
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

TokenID UnknownPatternAction(const char * lexeme) {
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	yylval.token = YYUNDEF;
	return YYUNDEF;
}

TokenID SymbolPatternAction(const char * lexeme) {
	LogDebug("SymbolPatternAction: '%s'.", lexeme);
	strcpy(yylval.string, lexeme);
	yylval.token = SYMBOL;
	return SYMBOL;
}

TokenID StringPatternAction(const char * lexeme) {
	strcpy(yylval.string, lexeme);
	yylval.token = STRING;
	LogDebug("StringPatternAction: '%s'.", lexeme);
	return STRING;
}