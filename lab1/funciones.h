#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dato
{
	char id[10];
	char r1[10];
	char r2[10];
	char r3[10];
};

typedef struct dato dato;

void procesar(dato* arregloinstrucciones, int lineas, int valores[32],char senal[10],FILE*salida, FILE*salida2);
/* 
	//===================================================================
ENTRADAS: arreglo con las instrucciones almacenadas en estructuras, cantidad de lineas de instruccion, señales de control, y archivos de salida
SALIDAS: como función no retorna nada, pero entrega ambos archivos de salida escritos con el procedimiento pedido
PROCEDIMIENTO: lee una a una las instrucciones del arreglo, y las ejecuta según las señales de control y posteriormente las escribe en los archivos de salida
	//===================================================================
*/
char* leerarchivo2(char* entrada2, char senal[10]);
/* 
	//===================================================================
ENTRADAS: archivo de entrada con las señales de control, y arreglo vacio para guardar estas ultimas
SALIDAS: arreglo de caracteres con las señales de control en el orden del archivo de entrada
PROCEDIMIENTO: lee el archivo de entrada, conserva el segundo caracter (señal activa/inactiva) y la guarda en un arreglo que posteriormente es retornado
	//===================================================================
*/
void leerarchivo(char* entrada, char senal[10],FILE* salida, FILE* salida2);
/* 
	//===================================================================
ENTRADAS: archivo de entrada con las instrucciones MIPS, arreglo con señales de control, y archivo de salida
SALIDAS: no retorna un valor como funcion, pero deja listas las instrucciones para procesarlas
PROCEDIMIENTO: lee el archivo con instrucciones, separando segun cada instruccion
los registros, direcciones y etiquetas, para finalmente almacenarlas en un arreglo de estructuras con cada registro y codigo de instruccion.
	//===================================================================
*/