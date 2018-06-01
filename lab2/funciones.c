#include "funciones.h"

lista* crearLista()
{
	/*crea una nueva lista, Entrada: sin entrada, Salida: puntero a estructura lista */
	lista* l;
	l = (lista*)malloc(sizeof(lista));
	l->inicio = NULL;
	l->fin = NULL;
	return l;free(l);
}

dato* crearnodo(char* id,char*rd,char*rs,char*rt, int verificador)
{
	/*recibe un numero con el que crea un nodo para agregar a la lista de adyacencia */
	dato* c;
	c=(dato*)malloc(sizeof(dato));
	c->siguiente=NULL;
	
	strcpy(c->id,id);
	strcpy(c->rd,rd);
	strcpy(c->rs,rs);
	strcpy(c->rt,rt);
	c->verificador=verificador;
	return c;free(c);
}

dato* buscar(lista* L,int indice){
	int i;
	i=0;
	dato* cursor = L -> inicio;
	while(cursor!=NULL){

		if(i==indice){
			return cursor;
		}
		i++;
		cursor = cursor -> siguiente;
	}
}
void encolar(lista* Q, dato* c)
{
/*recibe una lista y un nodo, lo agrega al final, devuelve la lista */
	if(Q->inicio==NULL)
	{
		Q->inicio=c;
		Q->fin=c;
	}
	else
	{
		
		Q->fin->siguiente=c;
		Q->fin=c;
	}

	c->siguiente = NULL;
}

void imprimirlista(lista* Q)
{
	/*imprime la lista */
	dato* cursor=Q->inicio;
	while(cursor!=NULL)
	{
		printf("%s %s %s %s\n",cursor->id,cursor->rd,cursor->rs,cursor->rt);
		//printf("%d\n",cursor->verificador );
		cursor=cursor->siguiente;
	}
	free(cursor);
}
int largolista(lista* Q)
{
	/*indica el largo de una lista*/
	int contador;
	contador=0;
	dato* cursor=Q->inicio;
	while(cursor!=NULL)
	{
		contador++;
		cursor=cursor->siguiente;
	}
	free(cursor);
	return contador;
}

lista* eliminaretiquetas(lista* Q)
{
	/*despeja la lista de etiquetas como NEXT*/
	dato* cursor=Q->inicio;
	while(cursor!=NULL)
	{
		dato*aux=cursor->siguiente;
		if(strcmp(cursor->id,"beq")==0){
			cursor->siguiente=aux->siguiente;
			free(aux);
		}
		else if(strcmp(cursor->id,"j")==0){
			cursor->siguiente=aux->siguiente;
			free(aux);
		}
		cursor=cursor->siguiente;
	}
	
	free(cursor);
}
void imprimirregistros(int* arreglo_registros){
	for (int i = 0; i < 32; ++i)
	{
		printf("%d ",arreglo_registros[i] );
	}
	printf("\n");
}
buffer* crearBuffer(){
	buffer* Buffer=(buffer*)malloc(sizeof(buffer));
	Buffer->id=(char*)malloc(sizeof(char));
	Buffer->rd=(char*)malloc(sizeof(char));
	Buffer->rs=(char*)malloc(sizeof(char));
	Buffer->rt=(char*)malloc(sizeof(char));
	strcpy(Buffer->id,"");
	strcpy(Buffer->rd,"");
	strcpy(Buffer->rs,"");
	strcpy(Buffer->rt,"");
	return Buffer;
}

pipeline* crearpipeline(char** nodo){
	pipeline* pipe;
	pipe=(pipeline*)malloc(sizeof(pipeline));
	pipe->linea=(char**)malloc(sizeof(char*)*5);
	for (int i = 0; i < 5; ++i)
	{
		pipe->linea[i]=(char*)malloc(sizeof(char));
	}
	strcpy(pipe->linea[0],nodo[0]);
	strcpy(pipe->linea[1],nodo[1]);
	strcpy(pipe->linea[2],nodo[2]);
	strcpy(pipe->linea[3],nodo[3]);
	strcpy(pipe->linea[4],nodo[4]);
	return pipe;
}
lista_pipeline* crearlista_pipe(){
	lista_pipeline* l;
	l = (lista_pipeline*)malloc(sizeof(lista_pipeline));
	l->inicio = NULL;
	l->fin = NULL;
	return l;free(l);
}
void encolar_pipe(lista_pipeline* Q, pipeline* c)
{
/*recibe una lista y un nodo, lo agrega al final, devuelve la lista */
	if(Q->inicio==NULL)
	{
		Q->inicio=c;
		Q->fin=c;
	}
	else
	{
		
		Q->fin->siguiente=c;
		Q->fin=c;
	}

	c->siguiente = NULL;
}
void imprimirpipe(lista_pipeline*pipe){
	pipeline* cursor = pipe->inicio;
	while(cursor!=NULL){
		printf("%s %s %s %s %s \n",cursor->linea[0],cursor->linea[1],cursor->linea[2],cursor->linea[3],cursor->linea[4] );
		cursor = cursor -> siguiente;
	}
	free(cursor);
}