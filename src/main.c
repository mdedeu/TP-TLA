#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include "frontend/syntactic-analysis/bison-actions.h"
#include <stdio.h>
#include "backend/semantic-analysis/symbol-table.h"

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
	init_symbol_table();
	const int result = yyparse();
	switch (result) {
		case 0:
			if (state.succeed) {
				LogInfo("La compilacion fue exitosa.");
				out = fopen("./target/Program.java", "w+");
				
				if (out == NULL)
				{
					perror("Error creating auxiliary file");
					exit(EXIT_FAILURE);
				}
				fprintf(out, "public class Program { \n	public static void main(String[] args) { \n");
				GeneratorProgram(state.mainProgram, out);
				fclose(out);
				char bytecode_command[512];
				sprintf(bytecode_command, "javac ./target/Program.java ./src/backend/domain-specific/*.java -d target");

				if( -1 == system(bytecode_command) ) {
					LogError("Se produjo un error en la aplicacion.");
					free_symbol_table();
					return -1;
				}
				
				sprintf(bytecode_command, "rm -rf ./target/*.java");

				if( -1 == system(bytecode_command) ) {
					LogError("Se produjo un error en la aplicacion.");
					free_symbol_table();
					return -1;
				}
			}
			else {
				LogError("Se produjo un error en la aplicacion.");
				free_symbol_table();
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
	free_symbol_table();
	LogInfo("Fin.");
	return result;
}
