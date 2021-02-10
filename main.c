/**
 * Librerías usadas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>  
#include "shell.h"

// Tamaño de buffer para cadena
#define TAM 1000 

/**
 * Método main
 * @param argc numero de argumentos
 * @param argv argumentos
 */
int main(int argc, char* argv[]) {
	char  cad[TAM];

	// Aseguramos que no tengamos argumentos extras
	checkArguments(argc);
	printf("ConsolaPractica5 $: Utilizar 'comandos' para ver órdenes disponibles\n");
	// Queremos que siempre se ejecute
	while (1) {
		printf("ConsolaPractica5 $: ");
		// fgets lee la linea desde stdin (el comando) y lo guarda en cad
		fgets(cad, TAM, stdin);

		// Si encuentra un salto de linea (se pulsa enter), lo marcamos como final de sentencia 
		if (cad[strlen(cad) - 1] == '\n') cad[strlen(cad) - 1] = '\0';   
        
		// Si no se escribe nada, continua funcionando esperando a la siguiente órden
		if (strlen(cad) == 0) continue;
		
		// Analiza lo introducido por línea de órdenes
		analizar(cad, argv);
		
		// Transforma los comandos a minúsculas
		minusculas(argv[0]);

		// Utilizamos los comandos
		callFunction(argv);
	}
	return 0;
}