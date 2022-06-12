#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-rules.h".
 */

yytoken_kind_t IntegerPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	yylval.integer = atoi(lexeme);
	yylval.token = INTEGER;
	return INTEGER;
}

void IgnoredPatternAction(const char * lexeme) {
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

yytoken_kind_t UnknownPatternAction(const char * lexeme) {
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	yylval.token = YYUNDEF;
	return YYUNDEF;
}

yytoken_kind_t SymbolPatternAction(const char * lexeme) {
	LogDebug("SymbolPatternAction: '%s'.", lexeme);
	strcpy(yylval.string, lexeme);
	yylval.token = SYMBOL;
	return SYMBOL;
}

yytoken_kind_t StringPatternAction(const char * lexeme) {
	strcpy(yylval.string, lexeme);
	yylval.token = STRING;
	LogDebug("StringPatternAction: '%s'.", lexeme);
	return STRING;
}