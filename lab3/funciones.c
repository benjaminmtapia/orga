#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"
/********************************
Funcion que escribe el estado de la mejor cache despues de la ultima consulta
Entrada: una cache, la cantidad de maximo hit
Procedimiento: Recorre la cache e imprime en el archivo de salida todos los elementos
*/
void escribirCache(Cache* cache, int maximoHit,FILE*archivo){

	fprintf(archivo, "%s\n","========================================================================" );
	for (int i = 0; i < cache->numerodeVias; i++){
		for(int j = 0; j < cache->bloquesPorVia; j++){
			for(int k = 0; k < cache->palabrasPorBloque; k++){
				fprintf(archivo, "via[%d] bloque[%d] palabra[%d]: %d\n", i,j,k,cache->vias[i].bloques[j].palabras[k] );
			}
		}
	}
}

/*********************************
Entrega la cantidad de bloques de una cache
*Entradas: Tamaño de dato en Bytes, y numero de Palabras por bloque
*Salida: Entrega la cantidad de bloques
*Proceso: Se divide el tamaño de datos por 4 y este por el numero de palabras por bloque
			para obtener la cantidad de bloques
*/
int cantidadBloques (int tamanoDatos, int PalporBloque){
	int resultado;
	//1 palabra -> 4 bytes
	resultado = tamanoDatos/4;
	//se divide por la cantidad de palabras por bloque
	resultado = resultado /PalporBloque;
	return resultado;
}

/*********************************
Verifica si una cache esta llena o no
*Entrada: una estructura de cache
*Salida: 1 si esta lleno, 0 si no esta lleno
*Procedimiento: Recorre todas las palabras viendo que todas sean distinto de -1, si ninguna es -1 esta lleno
*/
int EstaLleno(Cache* cache){
	int contador = 0 ;
	for (int i = 0; i < cache->numerodeVias; ++i){
		for(int j = 0; j < cache->bloquesPorVia; j++){

			for(int k = 0; k < cache->palabrasPorBloque; k++){
				if(cache->vias[i].bloques[j].palabras[k] != -1){
					contador++;
				}
			}
		}
	}
	if(contador == 0){
		return 1;
	}
	else{
		return 0;
	}
}

/*******************************************
Determina el numero maximo de hits
*Entradas: un arreglo con los hits de cada cache con cada politica
			[ [FIFO,LIFO,MRU,LRU] , [FIFO,LIFO,MRU,LRU],....]
*Salida: numero maximo de hits
*Proceso: Recorre todo y busca el hit maximo, retornando este mismo
*/
int determinarMax(int** hits, int cantidad){
	int maximo;
	maximo = hits[0][0];
	for (int i = 0; i < cantidad; i++)
	{
		for( int j = 0; j< 4;j++){
			if(maximo<hits[i][j]){
				maximo=hits[i][j];
			}

		}
	}
	return maximo;
}
/*********************************++*
Funcion que limpia una cache despues de haber aplicado una politica
Entrada: Una cache
Salida: Una cache vacia, con hit y miss en 0
Procedimiento: Recorre la cache, vaciando todas las palabras y colocando los hit y miss en 0
*/
Cache* LimpiarCache(Cache*cache){
	for (int i = 0; i < cache->numerodeVias; ++i){
		for(int j = 0; j < cache->bloquesPorVia; j++){

			for(int k = 0; k < cache->palabrasPorBloque; k++){
				
				cache->vias[i].bloques[j].palabras[k]=-1;
			}
		}
	}
	cache->hit = 0;
	cache->miss = 0;

	return cache;
}

/******
Funcion que lee un archivo con los datos y los guarda en un arreglo de enteros
Entrada: El nombre de archivo entregado por consola
Salida: Un arreglo con los datos del archivo
Procedimiento: Se realiza la lectura de archivo linea a linea y se guarda el elementno en un arreglo que se retorna al final
*/
int* leerArchivo(char* nombreArchivo, int palabrasPorBloque){
		FILE* archivo;
		archivo = fopen(nombreArchivo,"r");
		int largo = 0;
		char buffer[25*100];
		char* valor;
		valor = (char*)malloc(sizeof(char));

		if(archivo == NULL){
			printf("El archivo ingresado es incorrecto\n");
			exit(1);
		}
		while(!feof(archivo)){
			fgets(buffer, 25*100, archivo);
			largo++;
		}
		rewind(archivo);
		int* palabras;
		palabras = (int*)malloc(sizeof(int)*largo);

		int i = 0;
		while(!feof(archivo) && i < largo){
			fgets(buffer, 25*100, archivo);
			valor = strtok(buffer,"\n");
			palabras[i] = atoi(valor) /(4 * palabrasPorBloque);
			
			i++;

		}

	return palabras;
}

/***********************************
Funcion que Crea una cache
Entrada: palabras por bloque, tamaño de datos y numero de vias
Salida: una cache
Procedimiento: inica los hits y miss en 0, crea las vias y bloques, y deja las palabras en -1
*/
Cache* crearCache(int cantidadPalabras, int tamanoDatos, int numVias){
		Cache* cache;
		cache = (Cache*)malloc(sizeof(Cache));
		cache->hit = 0;
		cache->miss = 0;
		cache->numerodeVias = numVias;
		cache->palabrasPorBloque = cantidadPalabras;
		cache->numerodeBloques = cantidadBloques(tamanoDatos,cantidadPalabras);
		cache->bloquesPorVia = cache->numerodeBloques / cache->numerodeVias;
		cache->vias = (Via*)malloc(sizeof(Via)*numVias);

		for(int i =0; i < cache->numerodeVias; i++){

		cache->vias[i].bloques = (Bloque*)malloc(sizeof(Bloque)*cache->bloquesPorVia);
		cache->vias[i].MRU = 0;
		cache->vias[i].contador = 0;

		for(int j=0; j < cache->bloquesPorVia; j++){
			
			cache->vias[i].bloques[j].palabras = (int*)malloc(sizeof(int)*cache->palabrasPorBloque);
			cache->vias[i].bloques[j].LRU=0;

			for(int k=0 ; k < cache->palabrasPorBloque ; k++){
				cache->vias[i].bloques[j].palabras[k]=-1;
			}
		}
	}
	return cache;
}
/******************
Funcion que inserta un dato en una via y bloque especifico de la cache
Entrada: una cache, una via, un bloque y el dato a insertar
Procedimiento: Recorre las palabras en un bloque de una determinada via e inserta el dato
*/
void insertarDato(Cache* cache, int via, int bloque, int dato){
	int pos;
	for(int i=0; i < cache->palabrasPorBloque; i++){
		//se aplica principio de localidad espacial
		cache->vias[via].bloques[bloque].palabras[i] = dato - (dato%cache->palabrasPorBloque) + i;
	}

}
/**********************
Funcion que verifica si un dato esta en cache
Entrada: Cache y el dato que se buscara
Salida: 1 si se encuentra, 0 si no
Procedimiento: Recorre la cache y busca el dato en cada via y cada bloque
*/
int ExisteEnCache(Cache* cache, int dato){
	int cantidadPalabras;
	int cantidadVias;
	int cantidadCache;
	for (int i = 0; i < cache->numerodeVias ; i++)
	{
		for (int j = 0; j < cache->bloquesPorVia; j++)
		{
			for (int k = 0; k < cache->palabrasPorBloque; k++)
			{
				if(cache->vias[i].bloques[j].palabras[k]==dato){
					return 1;
				}
			}
		}
	}
	return 0;
}

/*********************
Funcion que a partir de una via y un dato en una cache, entrega un bloque
Entrada: una cache, una via y un dato
Salida: un entero con la posicion del bloque
Procedimiento: recorre la cache en la via enregada y si el dato esta, entrega el bloque en que se encuentra
*/

int IndexBloque(Cache* cache, int via, int dato){
	for (int i = 0; i < cache->bloquesPorVia; i++)
	{
		for (int j = 0; j < cache->palabrasPorBloque; j++)
		{
			if(cache->vias[via].bloques[i].palabras[j] == dato){
				return i;
			}
		}
	}
	return -1;
}
/*************
funcion que aumenta la variable LRU
entradas: una cache, una via y un bloque
procedimiento: aumenta todas las variables de LRU en 1 y la del bloque y via indicado la deja en 0
				por ser la ultima insertada
*/
void indexLRU(Cache* cache, int via, int bloque){
	for(int i = 0; i < cache->bloquesPorVia; i++){
		if(cache->vias[via].bloques[i].LRU != -1){
			cache->vias[via].bloques[i].LRU++;
		}
	}
	cache->vias[via].bloques[bloque].LRU = 0;
}
/***************
funcion usada en la politica mru, que indica el bloque mas viejo
entrada: cache y via
procedimiento: busca el bloque con mayor valor lru, es decir, el ultimo que se agrego
*/
int indicebloqueLRU(Cache* cache, int via){
	int max = cache->vias[via].bloques[0].LRU;
	int indice =0;
	int i;
	for( i = 1 ; i < cache->bloquesPorVia ; i++){
		if(max < cache->vias[via].bloques[i].LRU){
			max = cache->vias[via].bloques[i].LRU;
			indice = i;
		}
	}
	return indice;
}
/*******************
Aplica la politica de reemplazo FIFO
Entrada: una cache y un dato
Procedimiento: verifica si el dato esta en la cache dando hit, y sino aumenta miss y lo inserta
*/
void FIFO(Cache* cache, int dato){

	int via = dato  % cache->numerodeVias;
    int bloque = cache->vias[via].contador % cache->bloquesPorVia;

	if(ExisteEnCache(cache,dato)==1){
		cache->hit++;
	}
	else{
		cache->miss++;
		insertarDato(cache,via,bloque,dato);
		cache->vias[via].contador++;
	}

}
/**************************
Funcion que aplica la politica LIFO a una cache
Entrada: cache, dato
Procedimiento: Verifica si la cache esta llena o no, si esta vacia la llena igual que LIFO, y una vez llena aplica 
				la tecnica LIFO, donde solo cambia el ultimo elemento donde inserto.
*/
void LIFO(Cache* cache, int dato){

int via = cache->bloquesPorVia;
int bloque = cache->palabrasPorBloque;
	if(EstaLleno(cache) != 1){
		FIFO(cache,dato);
	}
	else{
		
		if(ExisteEnCache(cache,dato)==1){
			cache->hit++;
			
		}
		else{
			cache->miss++;
			cache->vias[cache->numerodeVias-1].bloques[cache->bloquesPorVia-1].palabras[cache->palabrasPorBloque-1]=dato; 
		}

	}
}
/*****************
Funcion que aplica la politica MRU
Entrada: cache y dato
Procedimiento: si la cache esta vacia la llena igual que FIFO, y una vez llena se aplica la politica MRU
				donde si existe el dato se aplica hit y la variable MRU es el bloque actual
				Si no esta el dato, se aplica miss y se inserta en el bloque que corresponde a la variable MRU


*/
void MRU(Cache* cache, int dato){
	int	via = dato % cache->numerodeVias;

	//primero se verifica que el cache este lleno
	if(EstaLleno(cache) != 1){
		//si esta lleno se procede a actuar igual que FIFO
		FIFO(cache,dato);

	}
	else{
		if(cache->vias[via].contador == cache->bloquesPorVia){
			cache->vias[via].MRU = cache->vias[via].contador-1;
			cache->vias[via].contador++;
		}
		if(ExisteEnCache(cache,dato) == 1){
			cache->hit++;
			
			cache->vias[via].MRU = IndexBloque(cache,via,dato);
			//se actualiza el indice MRU, ultimo bloque usado

		}
		else{
			cache->miss++;
			insertarDato(cache,via,cache->vias[via].MRU,dato);
		}
	}
}
/****************************
Funcion que aplica la politica LRU
Entrada: una cache y un dato a buscar
Procedimiento: Ve si el cache esta lleno o vacio en primer lugar. Si el cache esta lleno ve si el dato esta o no,
				y para ambos casos calcula el bloque y aumenta el contador de LRU
				Si el cache esta lleno, procede igual que el caso anterior, pero en caso de miss inserta un dato y cambia
				la variable LRU a 0 y aumenta en 1 la del resto, cosa de que al buscar con indicebloqueLRU usa la maxima
					es decir, la del dato mas antiguo.
*/
void LRU(Cache* cache, int dato){
	//se reemplaza por el que menos ha sido usado
	 int via;
    int bloque;  
    via = dato  % cache->numerodeVias;
    
    if ( !EstaLleno(cache) )
    {
        if ( ExisteEnCache(cache,dato))
        {
            cache->hit++;
            bloque = IndexBloque(cache,via,dato);
            indexLRU(cache,via,bloque);
        }
        else
        {
            bloque = cache->vias[via].contador % cache->bloquesPorVia;
            cache->miss++;
            insertarDato(cache,via,bloque, dato);
            indexLRU(cache,via,bloque);
            cache->vias[via].contador++;
        }
    }
    else
    {   
        if (ExisteEnCache(cache,dato))
        {
            cache->hit++;
            bloque = IndexBloque(cache,via,dato);
            indexLRU(cache,via,bloque);
        }
        else
        {
            cache->miss++;
            bloque = indicebloqueLRU(cache,via);
            insertarDato(cache,via,bloque, dato);
            indexLRU(cache,via,bloque);
        }
    }

}

/*********************
Funcion principal del programa que con los datos entregados por consola busca la mejor cache
Entradas: palabras por bloque, tamaño de datos y nombre de archivo
Procedimiento: Obtiene todas las vias posibles y crea un arreglo de cache segun la cantidad de datos disponibles
				Despues crea un arreglo de arreglos de enteros con 4 numeros que representan a los hits posibles de cada cache con
				cada politica.
				Aplica cada politica a la cache, la limpia y va con la siguiente guardando los resultados de hit y miss.
				Escribe los archivos pedidos con los maximos hit, y el estado de cada cache.

*/
void posiblesCache(int palabrasPorBloque, int tamanoDatos,char* nombreArchivo){
	
		int bloques = cantidadBloques(tamanoDatos,palabrasPorBloque);
		int cantidad = 0;
		int * palabras;
		palabras = leerArchivo(nombreArchivo,palabrasPorBloque);
		for (int i = 1; i <= bloques+1; i=2*i)
		{
			cantidad++;

		}
		Cache** listacaches= (Cache**)malloc(sizeof(Cache*)*cantidad);
		int j=0;
		int i=1;
		
			for (i = 1; i <= bloques+1; i=2*i){
			listacaches[j]=crearCache(palabrasPorBloque,tamanoDatos,i);
			j++;
		}
		//printf("%d\n",(Test(listacaches[0],palabras,nombreArchivo,"LIFO")) ->hit);
		int** hits;
		hits = (int**)malloc(sizeof(int*)*cantidad);
		for(int j = 0; j < cantidad; j++){
			hits[j] = (int*)malloc(sizeof(int)*4);
			for(int k = 0; k < 4; k++){
				hits[j][k] = 0;
			}
		}	
		for (int a = 0; a < cantidad; a++){

		hits[a][0] = (Test(listacaches[a],palabras,nombreArchivo,"FIFO"))->hit;
		LimpiarCache(listacaches[a]);
		hits[a][1] = Test(listacaches[a],palabras,nombreArchivo,"LIFO")->hit;
		LimpiarCache(listacaches[a]);
		hits[a][2] = Test(listacaches[a],palabras,nombreArchivo,"MRU")->hit;
		LimpiarCache(listacaches[a]);
		hits[a][3] = Test(listacaches[a],palabras,nombreArchivo,"LRU")->hit;
	//	printf("%d %d %d %d\n",hits[a][0],hits[a][1],hits[a][2],hits[a][3] );
	}
	
	FILE* salida1;
	FILE* salida2;
	salida1= fopen("salida1.txt","w");
	salida2= fopen("salida2.txt","w");
	int maximo = determinarMax(hits,cantidad);

	double tasahits=0;
	double tasamiss = 0;
	double total ;
	for(int a = 0; a < cantidad; a++){
		for(int b =0; b <4; b++){
			if(hits[a][b]==maximo){
				total = listacaches[a]->hit + listacaches[a]->miss;
				tasahits = listacaches[a]->hit / total;
				tasamiss = listacaches[a]->miss /total ;

				fprintf(salida1, "-----------\n%s %d\n","Grado de asociatividad: ",listacaches[a]->numerodeVias );
				fprintf(salida1, "%s %d\n%s %d\n","Numero de Hits: ",listacaches[a]->hit,"Numero de Miss:",listacaches[a]->miss );
				fprintf(salida1, "%s %f\n%s %f\n","Tasa de Hits: ",tasahits,"Tasa de Miss:",tasamiss );
				if(b==0){
					fprintf(salida1, "%s %s\n","Tecnica de Reemplazo: ","FIFO" );
				}
				if(b==1){
					fprintf(salida1, "%s %s\n","Tecnica de Reemplazo: ","LIFO" );
				}
				if(b==2){
					fprintf(salida1, "%s %s\n","Tecnica de Reemplazo: ","MRU" );
				}
				if(b==3){
					fprintf(salida1, "%s %s\n","Tecnica de Reemplazo: ","LRU" );
				}
			}
		}
	}
		for (int a = 0; a < cantidad; a++){

		hits[a][0] = (Test(listacaches[a],palabras,nombreArchivo,"FIFO"))->hit;
		if(hits[a][0] == maximo){
		escribirCache(Test(listacaches[a],palabras,nombreArchivo,"FIFO"),maximo,salida2);
		}
		LimpiarCache(listacaches[a]);
		hits[a][1] = Test(listacaches[a],palabras,nombreArchivo,"LIFO")->hit;
		if(hits[a][1] == maximo){
		escribirCache(Test(listacaches[a],palabras,nombreArchivo,"LIFO"),maximo,salida2);
		}
		LimpiarCache(listacaches[a]);
		hits[a][2] = Test(listacaches[a],palabras,nombreArchivo,"MRU")->hit;
		if(hits[a][2] == maximo){
		escribirCache(Test(listacaches[a],palabras,nombreArchivo,"MRU"),maximo,salida2);
		}
		LimpiarCache(listacaches[a]);
		hits[a][3] = Test(listacaches[a],palabras,nombreArchivo,"LRU")->hit;
		if(hits[a][3] == maximo){
			escribirCache(Test(listacaches[a],palabras,nombreArchivo,"LRU"),maximo,salida2);
		}
		
	}
	
}

/***********************
Funcion que para cada cache emplea una politica de reemplazo
Entradas: la cache, los datos, el nombre del archivo y la politica a usar
Salida: una cache actualizada
Procedimiento: lee el archivo para ver la cantidad de datos, y para cada dato va aplicando
				la politica de reemplazo indicada
*/
Cache* Test(Cache* cache, int* palabras, char* nombreArchivo, char* politica){
		int i = 0;
		int contador = 0 ;
		FILE* archivo;
		archivo = fopen(nombreArchivo,"r");
		int largo = 0;
		char buffer[25*100];
		char* valor;
		valor = (char*)malloc(sizeof(char));

		if(archivo == NULL){
			printf("El archivo ingresado es incorrecto\n");
			exit(1);
		}
		while(!feof(archivo)){
			fgets(buffer, 25*100, archivo);
			largo++;
		}

	fclose(archivo);

	for (int i = 0; i < largo; i++)
	{
		if(strcmp(politica,"FIFO")==0){
			FIFO(cache,palabras[i]);
		}
		 if(strcmp(politica,"LIFO")==0){
			LIFO(cache,palabras[i]);
		}
		 if(strcmp(politica,"MRU")==0){
			MRU(cache,palabras[i]);
		}
		 if(strcmp(politica,"LRU")==0){
			LRU(cache,palabras[i]);
		}
	}
return cache;
}
