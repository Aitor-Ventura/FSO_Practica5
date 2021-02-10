/**
 * Se tendrá que desarrollar un pequeño shell que recogerá líneas tecleadas por el usuario y las procesará como hace el shell que utiliza Linux.
 * 
 * v2
 */

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

/**
 * Método interno que crea un nuevo proceso pesado
 * @param pid id del proceso
 * @param argv que contiene la orden
 * @param status 
 */
void hijo(pid_t pid, char* argv[], int status);

/**
 * Indica el error que se encuentra a través de un código de error que se pasa por parámetro
 * @param eCode código de error
 */
void check_error(int eCode){
	switch (eCode){
		case 0:
			fprintf(stderr, "[!] Invocación incorrecta: ./shell\n");
            exit(-1);
		case 1:
			printf("[!] Error al crear los procesos\n");
     		exit(1);
		case 2:
			printf("[!] No se encontró la órden\n");
			exit(1);
	}
}

/**
 * Se asigna a argv la orden
 * @param orden que se debe asignar
 * @param argv donde se asigna
 */
void analizar(char *orden, char **argv){
	while (*orden != '\0') {       
		if (*orden == ' ' || *orden == '\t' || *orden == '\n') *orden++ = '\0';     
		*argv++ = orden;
		while (*orden != '\0' && *orden != ' ' && *orden != '\t' && *orden != '\n') orden++;             
	} 
	*argv = '\0';    
}

/**
 * Método que transforma la ristra pasada por parámetro a minúsculas
 * @param str string a transformar a minúsculas
 * @return string transformada
 */
char* minusculas(char *str){
	char *p = str;
	while (*p) {
		// la función tolower devuelve el equivalente minúscula del parámetro pasado si existiera, si no no cambiaría
		*p = tolower(*p);
		p++;
	}
	return str;
}

/**
 * Método que asegura que no se pasen parámetros a la órden
 * @param argc numero de argumentos
 */
void checkArguments(int argc){
	if (argc > 1) check_error(0);
}

/**
 * Método que muestra por pantalla las instrucciones implementadas
 */
void comandos(){
	printf("\n--- PRACTICA 5 ---\n");
	printf("Instrucciones implementadas:\n");
	printf(">> cd\n");
	printf(">> exit\n");
	printf(">> cualquier otra órden de Linux\n");
	printf("Usar a propio riesgo\n\n");
}

/**
 * Método que implementa "cd", cambia directorio
 * @param argv que contiene el directorio a acceder
 */
void comcd(char *argv[]){
	// Retorno al directorio anterior si no se escribe nada posterior a 'cd'
	if(argv[1] == NULL) chdir("..");
	// Cambiar al directorio especificado
	chdir(argv[1]);
}

/**
 * Método interno que crea un nuevo proceso pesado
 * @param pid id del proceso
 * @param argv que contiene la orden
 * @param status 
 */
void hijo(pid_t pid, char* argv[], int status){
	// Crea proceso pesado
	pid = fork();
	// Controla caso de error
	if (pid  < 0) check_error(1);
	// Hijo
	else if (pid == 0) {
		// Ejecutamos la orden con el proceso hijo, a no ser que sea erroneo
		if (execvp(*argv, argv) < 0) check_error(2);
	}
	// Esperamos a que termine el proceso hijo                
	waitpid(pid,&status,0);
}

/**
 * Método que llama a las funciones implementadas y si no crea un proceso
 * @param argv que contiene las órdenes
 */
void callFunction(char* argv[]){
	pid_t pid;
	int status;
	/**
	 * strcmp devuelve 0 cuando ambas strings son iguales
	 * if (0) se trata como if (false), luego no entraría en ejecutar la instrucción cuando se quiere ejecutar la instrucción dentro de la condición
	 * luego !false == true y se ejecutaría
	 */
	// Help para mostrar lo implementado, continue para que no muestre "esa orden no se encuentra"
	if (!strcmp(argv[0], "comandos")) comandos();
	// Exit para salir del shell
	else if (!strcmp(argv[0], "exit")) exit(0);  
	// Implementación del comando CD
	else if (!strcmp(argv[0], "cd")) comcd(argv);
	else hijo(pid, argv, status);
}