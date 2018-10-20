#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct Bloque{
	int* palabras;
	int LRU;
};
typedef struct Bloque Bloque;

struct Via{
	//Array de bloques = conjunto
	Bloque* bloques;
	int contador;
	int MRU;
};
typedef struct Via Via;

struct Cache
{
	Via* vias;
	int hit;
	int miss;
	int numerodeVias;
	int numerodeBloques;
	int palabrasPorBloque;
	int bloquesPorVia;
};
typedef struct Cache Cache;
int ExisteEnCache(Cache* cache, int dato);
int tamanoCache(int tamanoDatos);
/*********************************
Entrega la cantidad de bloques de una cache
*Entradas: Tamaño de dato en Bytes, y numero de Palabras por bloque
*Salida: Entrega la cantidad de bloques
*Proceso: Se divide el tamaño de datos por 4 y este por el numero de palabras por bloque
			para obtener la cantidad de bloques
*/
int cantidadBloques (int tamanoDatos, int PalporBloque);
/*********************************
Verifica si una cache esta llena o no
*Entrada: una estructura de cache
*Salida: 1 si esta lleno, 0 si no esta lleno
*Procedimiento: Recorre todas las palabras viendo que todas sean distinto de -1, si ninguna es -1 esta lleno
*/
int EstaLleno(Cache* cache);
/*******************************************
Determina el numero maximo de hits
*Entradas: un arreglo con los hits de cada cache con cada politica
			[ [FIFO,LIFO,MRU,LRU] , [FIFO,LIFO,MRU,LRU],....]
*Salida: numero maximo de hits
*Proceso: Recorre todo y busca el hit maximo, retornando este mismo
*/
int determinarMax(int** hits, int cantidad);
/*********************************++*
Funcion que limpia una cache despues de haber aplicado una politica
Entrada: Una cache
Salida: Una cache vacia, con hit y miss en 0
Procedimiento: Recorre la cache, vaciando todas las palabras y colocando los hit y miss en 0
*/
Cache* LimpiarCache(Cache*cache);
/******
Funcion que lee un archivo con los datos y los guarda en un arreglo de enteros
Entrada: El nombre de archivo entregado por consola
Salida: Un arreglo con los datos del archivo
Procedimiento: Se realiza la lectura de archivo linea a linea y se guarda el elementno en un arreglo que se retorna al final
*/
int* leerArchivo(char* nombreArchivo, int palabrasPorBloque);
/***********************************
Funcion que Crea una cache
Entrada: palabras por bloque, tamaño de datos y numero de vias
Salida: una cache
Procedimiento: inica los hits y miss en 0, crea las vias y bloques, y deja las palabras en -1
*/
Cache* crearCache(int cantidadPalabras, int tamanoDatos, int numVias);

/******************
Funcion que inserta un dato en una via y bloque especifico de la cache
Entrada: una cache, una via, un bloque y el dato a insertar
Procedimiento: Recorre las palabras en un bloque de una determinada via e inserta el dato
*/
void insertarDato(Cache* cache, int via, int bloque, int dato);
/**********************
Funcion que verifica si un dato esta en cache
Entrada: Cache y el dato que se buscara
Salida: 1 si se encuentra, 0 si no
Procedimiento: Recorre la cache y busca el dato en cada via y cada bloque
*/
int ExisteEnCache(Cache* cache, int dato);
/*********************
Funcion que a partir de una via y un dato en una cache, entrega un bloque
Entrada: una cache, una via y un dato
Salida: un entero con la posicion del bloque
Procedimiento: recorre la cache en la via enregada y si el dato esta, entrega el bloque en que se encuentra
*/

int IndexBloque(Cache* cache, int via, int dato);
/*************
funcion que aumenta la variable LRU
entradas: una cache, una via y un bloque
procedimiento: aumenta todas las variables de LRU en 1 y la del bloque y via indicado la deja en 0
				por ser la ultima insertada
*/
void indexLRU(Cache* cache, int via, int bloque);
/***************
funcion usada en la politica mru, que indica el bloque mas viejo
entrada: cache y via
procedimiento: busca el bloque con mayor valor lru, es decir, el ultimo que se agrego
*/
int indicebloqueLRU(Cache* cache, int via);
/*******************
Aplica la politica de reemplazo FIFO
Entrada: una cache y un dato
Procedimiento: verifica si el dato esta en la cache dando hit, y sino aumenta miss y lo inserta
*/
void FIFO(Cache* cache, int dato);
/**************************
Funcion que aplica la politica LIFO a una cache
Entrada: cache, dato
Procedimiento: Verifica si la cache esta llena o no, si esta vacia la llena igual que LIFO, y una vez llena aplica 
				la tecnica LIFO, donde solo cambia el ultimo elemento donde inserto.
*/
void LIFO(Cache* cache, int dato);
/*****************
Funcion que aplica la politica MRU
Entrada: cache y dato
Procedimiento: si la cache esta vacia la llena igual que FIFO, y una vez llena se aplica la politica MRU
				donde si existe el dato se aplica hit y la variable MRU es el bloque actual
				Si no esta el dato, se aplica miss y se inserta en el bloque que corresponde a la variable MRU


*/
void MRU(Cache* cache, int dato);
/****************************
Funcion que aplica la politica LRU
Entrada: una cache y un dato a buscar
Procedimiento: Ve si el cache esta lleno o vacio en primer lugar. Si el cache esta lleno ve si el dato esta o no,
				y para ambos casos calcula el bloque y aumenta el contador de LRU
				Si el cache esta lleno, procede igual que el caso anterior, pero en caso de miss inserta un dato y cambia
				la variable LRU a 0 y aumenta en 1 la del resto, cosa de que al buscar con indicebloqueLRU usa la maxima
					es decir, la del dato mas antiguo.
*/
void LRU(Cache* cache, int dato);
/*********************
Funcion principal del programa que con los datos entregados por consola busca la mejor cache
Entradas: palabras por bloque, tamaño de datos y nombre de archivo
Procedimiento: Obtiene todas las vias posibles y crea un arreglo de cache segun la cantidad de datos disponibles
				Despues crea un arreglo de arreglos de enteros con 4 numeros que representan a los hits posibles de cada cache con
				cada politica.
				Aplica cada politica a la cache, la limpia y va con la siguiente guardando los resultados de hit y miss.
				Escribe los archivos pedidos con los maximos hit, y el estado de cada cache.

*/
void posiblesCache(int palabrasPorBloque, int tamanoDatos,char* nombreArchivo);
/***********************
Funcion que para cada cache emplea una politica de reemplazo
Entradas: la cache, los datos, el nombre del archivo y la politica a usar
Salida: una cache actualizada
Procedimiento: lee el archivo para ver la cantidad de datos, y para cada dato va aplicando
				la politica de reemplazo indicada
*/
Cache* Test(Cache* cache, int* palabras, char* nombreArchivo,char* politica);
int determinarMax(int** hits, int cantidad);