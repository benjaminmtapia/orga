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
	//busca un elemento en una lista enlazada de acuerdo a una posicion y retorna el nodo
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
		/*if(strcmp(cursor->id,"beq")==0 || strcmp(cursor->id,"j")==0){
			cursor->siguiente=aux->siguiente;
			free(aux);
		}*/
		if(cursor->siguiente!=NULL && strcmp(cursor->siguiente->id,"add")!=0 && strcmp(cursor->siguiente->id,"sub")!=0 && 
			strcmp(cursor->siguiente->id,"mul")!=0 && strcmp(cursor->siguiente->id,"div")!=0 && 
			strcmp(cursor->siguiente->id,"addi")!=0 && strcmp(cursor->siguiente->id,"subi")!=0 && 
			strcmp(cursor->siguiente->id,"beq")!=0 && strcmp(cursor->siguiente->id,"j")!=0 && 
			strcmp(cursor->siguiente->id,"lw")!=0 && strcmp(cursor->siguiente->id,"sw")!=0  ){
			
			cursor->siguiente=aux->siguiente;
		}
		cursor=cursor->siguiente;
	}
	
	free(cursor);
}
void imprimirregistros(int* arreglo_registros){
	//imprime los 32 registros dado un arreglo con sus valores
	//Entrada: arreglo de registros
	for (int i = 0; i < 32; ++i)
	{
		printf("%d ",arreglo_registros[i] );
	}
	printf("\n");
}
buffer* crearBuffer(){
	//crea una estructura buffer
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
	//crea una estructura de pipeline con 5 etapas
	//Entrada: arreglo de strings
	//Salida: nodo de pipeline con 5 etapas con una instruccion ya cargada
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
	//crea una lista para nodos de pipeline
	lista_pipeline* l;
	l = (lista_pipeline*)malloc(sizeof(lista_pipeline));
	l->inicio = NULL;
	l->fin = NULL;
	return l;free(l);
}
void encolar_pipe(lista_pipeline* Q, pipeline* c){
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
void imprimirpipe(lista_pipeline* Q)
{
	/*imprime la lista */
	pipeline* cursor=Q->inicio;
	while(cursor!=NULL)
	{
		printf("%s || %s || %s || %s || %s\n",cursor->linea[0],cursor->linea[1],cursor->linea[2],cursor->linea[3],cursor->linea[4]);
		cursor=cursor->siguiente;
	}
	free(cursor);
}
int lineas (char*entrada){
	//entrega la cantidad de lineas de codigo a partir de un codigo MIPS
	//Entrada: NOMBRE DE ARCHIVO
		FILE*archivo;
		char buffer[30];
		archivo=fopen("M1.asm","r");
		int aux=0;
		while(!feof(archivo)){
			fgets(buffer,1000,archivo);
			aux++;
		}
		return aux;
}
dato* leerarchivo(char* entrada, dato* arregloinstrucciones){
	//lee un archivo con codigo mips y lo retorna como un arreglo de estructuras
	//Entrada: nombre de archivo, arreglo de instrucciones a modificar
	//salida: arreglo de instrucciones con codigo mips
		FILE* archivo;
		lista*L;
		L=crearLista();
		dato* nodo;
		nodo=(dato*)malloc(sizeof(dato));

		archivo=fopen(entrada,"r");
		char buffer[1000];
		int lineas=0;

		if(archivo==NULL){
		printf("%s\n","Falló apertura de archivo de programa" );
		exit(1);
		}
		while(!feof(archivo)){
		fgets(buffer, 1000, archivo);
		lineas++;
		}	
		fclose(archivo);

		int aux=0;
		arregloinstrucciones=(dato*)malloc(sizeof(dato)*lineas);
		archivo=fopen(entrada,"r");
		char buffer2[1000];

		char*valor;char*valor2;char*valor3;char*valor4;

		while(!feof(archivo) && aux<lineas){
		fgets(buffer, 1000, archivo);
		valor 	= strtok(buffer, " ");
		if(strcmp(valor,"add")==0 ||strcmp(valor,"sub")==0 ||strcmp(valor,"mul")==0 ||strcmp(valor,"div")==0 ||
		strcmp(valor,"addi")==0 ||strcmp(valor,"subi")==0 ||strcmp(valor,"beq")==0  ){
				strcpy(arregloinstrucciones[aux].id,valor);
				valor2 	= strtok(NULL,", ");
				strcpy(arregloinstrucciones[aux].rd,valor2);
				valor3 	= strtok(NULL,", ");
				strcpy(arregloinstrucciones[aux].rs,valor3);
				valor4	= strtok(NULL," \n");
				strcpy(arregloinstrucciones[aux].rt,valor4);

				//nodo=crearnodo(valor,valor2,valor3,valor4);
				//encolar(L,nodo);

		}
		else if(strcmp(valor,"j")==0){
				strcpy(arregloinstrucciones[aux].id,valor);
				valor2 	= strtok(NULL," \n");
				strcpy(arregloinstrucciones[aux].rd,valor2);
				valor3="";
				valor4="";
				strcpy(arregloinstrucciones[aux].rs,valor3);
				strcpy(arregloinstrucciones[aux].rt,valor4);
		}
		
		else if(strcmp(valor,"lw")==0 || strcmp(valor,"sw")==0){
				strcpy(arregloinstrucciones[aux].id,valor);
				valor2 	= strtok(NULL,", ");
				strcpy(arregloinstrucciones[aux].rd,valor2);
				valor3 	= strtok(NULL," (");
				strcpy(arregloinstrucciones[aux].rs,valor3);
				valor4	= strtok(NULL,")");
				strcpy(arregloinstrucciones[aux].rt,valor4);
		}
		else{
			valor=strtok(valor,":\n");
			strcpy(arregloinstrucciones[aux].id,valor);
			valor2="";
			valor3="";
			valor4="";
			strcpy(arregloinstrucciones[aux].rd,valor2);
			strcpy(arregloinstrucciones[aux].rs,valor3);
			strcpy(arregloinstrucciones[aux].rt,valor4);
		}
	aux++;
}
fclose(archivo);
return arregloinstrucciones;
}
int* leerarchivo2(char* entrada2, int* arreglo_registros){
	//funcion que lee un archivo con los valores de registros y los deja en un arreglo de enteros
	//Entradas: nombre de archivo, arreglo de enteros a modificar
	//Salida: arreglo de enteros con los valores de los registros
	FILE* archivo;
	archivo=fopen(entrada2,"r");
	char buffer[1000];
	int lineas=0;

		if(archivo==NULL){
		printf("%s\n","Falló apertura de archivo de programa" );
		exit(1);
		}
		while(!feof(archivo)){
		fgets(buffer, 1000, archivo);
		lineas++;
		}	
		fclose(archivo);
	
	arreglo_registros=(int*)malloc(sizeof(int)*32);

	for (int i = 0; i < 32; ++i){
		arreglo_registros[i]=0; 
	}
	archivo=fopen(entrada2,"r");
	int aux; aux=0;

	char*valor;char*valor2;char*valor3;char*valor4;
	int valor_registro;

		while(!feof(archivo) && aux<lineas){
		fgets(buffer, 1000, archivo);
		valor 	= strtok(buffer, " ");
		valor2	= strtok(NULL,"");
		valor_registro=atoi(valor2);
		arreglo_registros[aux]=valor_registro;
		aux++;
		}
		fclose(archivo);
	return arreglo_registros;
}
char* unir_instruccion(char*id,char*rd,char*rs,char*rt){
	//une una funcion mips y sus 3 registros en un solo string
	//Entrada: instruccion, registro 1, registro 2, registro 3
	//Salida: instruccion
	char*aux;
	aux=(char*)malloc(sizeof(char));
	strcpy(aux,id);
	strcat(aux," ");
	strcat(aux,rd);
	strcat(aux,", ");
	strcat(aux,rs);
	strcat(aux,", ");
	strcat(aux,rt);
	return aux;
}


void change_buffer(buffer* IFID, buffer* IDEX, buffer* EXMEM, buffer* MEMWB, char* id, char*rd, char*rs, char* rt){
	//funcion que hace un push a los buffers y los entrega desplazados
	//Entrada: 4 buffers y una instruccion dividida en instruccion y sus 3 registros
	//Salida: no retorna un valor, pero modifica los buffers
	strcpy(MEMWB->rd,EXMEM->rd);
	strcpy(MEMWB->rs,EXMEM->rs);
	strcpy(MEMWB->rt,EXMEM->rt);
	strcpy(MEMWB->id,EXMEM->id);
	strcpy(EXMEM->id,IDEX->id);
	strcpy(EXMEM->rd,IDEX->rd);
	strcpy(EXMEM->rs,IDEX->rs);
	strcpy(EXMEM->rt,IDEX->rt);
	strcpy(IDEX->id,IFID->id);
	strcpy(IDEX->rd,IFID->rd);
	strcpy(IDEX->rs,IFID->rs);
	strcpy(IDEX->rt,IFID->rt);
	strcpy(IFID->rd,rd);
	strcpy(IFID->rs,rs);
	strcpy(IFID->rt,rt);
	strcpy(IFID->id,id);
}

int detectar_hazard(buffer* EXMEM,buffer*IDEX,buffer*MEMWB){
	//dado dos buffers retorna si hay hazard o no
	//entrada: 3 buffers que podrian contener hazards
	//salida: un entero que cumple funcion de booleano si es que hay hazard o no (1 es true y 0 es false)
	if(strcmp(EXMEM->rd,IDEX->rs)==0){
		return 1;
	}
	else if(strcmp(EXMEM->rd,IDEX->rt)==0){
		return 1;
	}
	else if(strcmp(MEMWB->rd,EXMEM->rs)==0){
		return 1;
	}
	else if(strcmp(MEMWB->rd,EXMEM->rt)==0){
		return 1;
	}
	else{
		return 0;
	}
}
void agregarNOP(pipeline* pipe){
	//corre las etapas de un pipeline agregando un nop
	//Entrada: un nodo de pipeline con 5 etapas
	strcpy(pipe->linea[4],pipe->linea[3]);
	strcpy(pipe->linea[3],pipe->linea[2]);
	strcpy(pipe->linea[2],pipe->linea[1]);
	strcpy(pipe->linea[1],pipe->linea[0]);
	strcpy(pipe->linea[0],"NOP");
}
void escribir_pipeline(pipeline* pipe,char* aux){
	//modifica un nodo de pipeline agregando una nueva instruccion
	//entrada: un nodo de pipeline y una instruccion char*
	//salida: no retorna un valor, pero modifica el nodo del pipeline
	strcpy(pipe->linea[4],pipe->linea[3]);
	strcpy(pipe->linea[3],pipe->linea[2]);
	strcpy(pipe->linea[2],pipe->linea[1]);
	strcpy(pipe->linea[1],pipe->linea[0]);
	strcpy(pipe->linea[0],aux);
}
void mover_final(char** linea, char* aux){
	//funcion usada para la ultima instruccion del pipeline, corre la linea y va agregando un caracter aux que son guiones (-)
	//entrada: arreglo char con 5 etapas de pipeline y caracter a agregar
	//cambia el pipeline para terminarlo
	strcpy(linea[4],linea[3]);
	strcpy(linea[3],linea[2]);
	strcpy(linea[2],linea[1]);
	strcpy(linea[1],linea[0]);
	strcpy(linea[0],aux);
}
int buscador(char*** codigo, int largo){
	//busca la etiqueta en una instruccion beq y entrega su indice
	//recibe un codigo char*** y su extension
	//retorna un entero que contiene la posicion de la etiqueta
	char* etiqueta;
	int indice;
	etiqueta = (char*)malloc(sizeof(char));
	for (int i = 0; i < largo; ++i)
	{
//printf("%s\n",codigo[i][0] );
		if(strcmp(codigo[i][0],"beq")==0){
			strcpy(etiqueta,codigo[i][3]);
			etiqueta=strtok(etiqueta," ");
			//printf("%s\n",etiqueta );
		}
	}
	for (int i = 0; i < largo; ++i)
	{
		if(strcmp(etiqueta,codigo[i][0])==0){
			//printf("etiqueta aqui %s\n",codigo[i][0]);
			indice=i;
		}
	}
	return indice;
}
int buscadorJ(char*** codigo, int largo){
	//busca la etiqueta en una instruccion jump y entrega su indice
	//recibe un codigo char*** y su extension
	//retorna un entero que contiene la posicion de la etiqueta
	char* etiqueta;
	int indice;
	etiqueta = (char*)malloc(sizeof(char));
	for (int i = 0; i < largo; ++i)
	{
//printf("%s\n",codigo[i][0] );
		if(strcmp(codigo[i][0],"j")==0){
			strcpy(etiqueta,codigo[i][3]);
			etiqueta=strtok(etiqueta," ");
			//printf("%s\n",etiqueta );
		}
	}
	for (int i = 0; i < largo; ++i)
	{
		if(strcmp(etiqueta,codigo[i][0])==0){
			//printf("etiqueta aqui %s\n",codigo[i][0]);
			indice=i;
		}
	}
	return indice;
}

pipeline* corregirNodo(pipeline* nodo, char* ins){
	for (int i = 0; i < 5; i++){
		if(strcmp(nodo->linea[i],ins)==0){
			strcpy(nodo->linea[i],"NOP");
		}
	
	}
	return nodo;
}