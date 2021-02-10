/**
 * Indica el error que se encuentra a través de un código de error que se pasa por parámetro
 * @param eCode código de error
 */
void check_error(int eCode);

/**
 * Se asigna a argv la orden
 * @param orden que se debe asignar
 * @param argv donde se asigna
 */
void  analizar(char *orden, char **argv);

/**
 * Método que transforma la ristra pasada por parámetro a minúsculas
 * @param str string a transformar a minúsculas
 * @return string transformada
 */
char* minusculas(char *str);

/**
 * Método que muestra por pantalla las instrucciones implementadas
 */
void comandos();

/**
 * Método que llama a las funciones implementadas y si no crea un proceso
 * @param argv que contiene las órdenes
 */
void callFunction(char* argv[]);

/**
 * Método que implementa "cd", cambia directorio
 * @param argv que contiene el directorio a acceder
 */
void comcd(char *argv[]);

/**
 * Método que asegura que no se pasen parámetros a la órden
 * @param argc numero de argumentos
 */
void checkArguments(int argc);