#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dato
{
	char id[10];
	char rd[10];
	char rs[10];
	char rt[10];
	int verificador;
	struct dato* siguiente;
};
typedef struct dato dato;
struct buffer
{
	char* id;
	char* rd;
	char* rs;
	char* rt;
};
typedef struct buffer buffer;

struct lista
{
	dato* inicio;
	dato* fin;
};
typedef struct lista lista;


struct pipeline
{
	char** linea;
	struct pipeline* siguiente;
};
typedef struct pipeline pipeline;

struct lista_pipeline
{
	pipeline*inicio;
	pipeline*fin;
};
typedef struct lista_pipeline lista_pipeline;



lista* crearLista();
dato* crearnodo(char* id,char*rd,char*rs,char*rt, int verificador);
void encolar(lista* Q, dato* c);
dato* buscar(lista* L,int indice);
void imprimirlista(lista* Q);
int largolista(lista* Q);
lista* eliminaretiquetas(lista* Q);
int ejecutar(dato* arregloinstrucciones,int* valores, int lineas, int a, lista*L);
int lineas (char*entrada);
dato* leerarchivo(char* entrada, dato* arregloinstrucciones);
int* leerarchivo2(char* entrada2, int* arreglo_registros);
void imprimirregistros(int* arreglo_registros);
void salida1(FILE*salida,dato* arregloinstrucciones, int* arreglo_registros, int lineas);
char* unir_instruccion(char*id,char*rd,char*rs,char*rt);
buffer* crearBuffer();
pipeline* crearpipeline(char** nodo);
lista_pipeline* crearlista_pipe();
void encolar_pipe(lista_pipeline*Q,pipeline*c);
void imprimirpipe(lista_pipeline*pipe);