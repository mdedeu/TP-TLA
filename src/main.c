#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include "frontend/syntactic-analysis/bison-actions.h"
#include <stdio.h>

//Estado de la aplicación.
CompilerState state;
FILE * out;
int yyparse();

// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char ** arguments) {
	// Inicializar estado de la aplicación.
	state.result = 0;
	state.succeed = false;
	state.mainProgram = NULL;

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
	const int result = yyparse();
	switch (result) {
		case 0:
			if (state.succeed) {
				LogInfo("La compilacion fue exitosa.");
				out = fopen("Test.java", "w+");
				if (out == NULL)
				{
					perror("Error creating auxiliary file");
					exit(EXIT_FAILURE);
				}
				fprintf(out, "public class Test { \n	public static void main(String[] args) { \n");
				GeneratorProgram(state.mainProgram, out);

			}
			else {
				LogError("Se produjo un error en la aplicacion.");
				return -1;
			}
			break;
		case 1:
			LogError("Bison finalizo debido a un error de sintaxis.");
			break;
		case 2:
			LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
			break;
		default:
			LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	LogInfo("Fin.");
	return result;
}
