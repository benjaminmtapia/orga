#include "funciones.h"

int ejecutar(dato* arregloinstrucciones,int* valores, int lineas, int a, lista*L){

	//printf("%d\n",lineas );
	char* inmediato;int inmediate;
	//REGISTROS
	char*registros[32]={"$zero","$at","$v0","$v1","$a0",
	"$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5",
	"$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6",
	"$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};
	//MEMORIA PARA LW Y SW
	int memoria[1024];
	for (int i = 0; i < 1024; ++i)
	{
		memoria[i]=0;
	}
	//INDICES PARA LOS ARREGLOS
	int dato1,dato2,dato3;
	dato1=0;dato2=0;dato3=0;

	int direccion;
	int posicion;
	direccion=0;
	//LECTURA DE INSTRUCCIONES
	
		if(strcmp("j",arregloinstrucciones[a].id)==0){
			int indice=0;
			arregloinstrucciones[a].verificador=1;
			inmediato=strtok(arregloinstrucciones[a].rd," \n");
			
				for(int i=0; i < lineas; i++){

					if(strcmp(inmediato,arregloinstrucciones[i].id)==0){
						indice=i;
						break;
					}
				}
				a=indice;
			
		}
		//INSTRUCCIONES ADD,SUB,MUL,DIV
		else if(strcmp("add",arregloinstrucciones[a].id)==0 || strcmp("sub",arregloinstrucciones[a].id)==0 ||
			strcmp("mul",arregloinstrucciones[a].id)==0 || strcmp("div",arregloinstrucciones[a].id)==0){
			arregloinstrucciones[a].verificador=1;

			//printf("%d\n",arregloinstrucciones[a].verificador );
			inmediato=strtok(arregloinstrucciones[a].rt," \n");
			for(int i=0; i < 32; i++){

				if(strcmp(arregloinstrucciones[a].rd,registros[i])==0){
					
				dato1=i;
				}
				 if(strcmp(arregloinstrucciones[a].rs,registros[i])==0){
				 	
				dato2=i;
				}
				 if(strcmp(arregloinstrucciones[a].rt,registros[i])==0){
				 	
				dato3=i;
				}
			}

			if(strcmp("add",arregloinstrucciones[a].id)==0){
				valores[dato1]=valores[dato2]+valores[dato3];
			}
			else if(strcmp("sub",arregloinstrucciones[a].id)==0){
				valores[dato1]=valores[dato2]-valores[dato3];
			}
			else if(strcmp("mul",arregloinstrucciones[a].id)==0){
				valores[dato1]=valores[dato2]*valores[dato3];
			}
			else{
				valores[dato1]=valores[dato2]/valores[dato3];
			}

			a++;
		}
		//INSTRUCCIONES ADDI Y SUBI
		else if(strcmp("addi",arregloinstrucciones[a].id)==0 || strcmp("subi",arregloinstrucciones[a].id)==0){
		arregloinstrucciones[a].verificador=1;

			//printf("%d\n",arregloinstrucciones[a].verificador );
			inmediato=strtok(arregloinstrucciones[a].rt," \n");
			inmediate=atoi(inmediato);
			//printf("%d\n",inmediate );
			for (int i = 0; i < 32; i++){
				if(strcmp(arregloinstrucciones[a].rd,registros[i])==0){
					dato1=i;
				}
				 if(strcmp(arregloinstrucciones[a].rs,registros[i])==0){
					dato2=i;
				}
			}
			
				if(strcmp("addi",arregloinstrucciones[a].id)==0){

					valores[dato1]=valores[dato2]+inmediate;
				}
				else{
					valores[dato1]=valores[dato2]-inmediate;
				}
				a++;
		}
		//INSTRUCCIONES LW Y SW
			else if(strcmp("lw",arregloinstrucciones[a].id)==0 ){
				arregloinstrucciones[a].verificador=1;

		//	printf("%d\n",arregloinstrucciones[a].verificador );
				for(int i=0; i < 32; i++){
					if(strcmp(arregloinstrucciones[a].rd,registros[i])==0){
					dato1=i;
					
				}
				else if(strcmp(arregloinstrucciones[a].rt,registros[i])==0){
					dato3=i;
						}
					}
				int dir=atoi(arregloinstrucciones[a].rs);
				if(dir%4!=0){
					printf("%s\n","la direccion de memoria no es divisible de 4" );
					exit(1);
				}
				direccion=dir/4;
				for(int i=0 ; i < 1024; i++){
						valores[dato1]=memoria[direccion];
				}
				a++;
		}

		else if(strcmp("sw",arregloinstrucciones[a].id)==0){
			arregloinstrucciones[a].verificador=1;

			//printf("%d\n",arregloinstrucciones[a].verificador );
				for(int i=0; i < 32; i++){
					if(strcmp(arregloinstrucciones[a].rd,registros[i])==0){
					dato1=i;
					
				}
				else if(strcmp(arregloinstrucciones[a].rt,registros[i])==0){
					dato3=i;
						}
					}
				int dir=atoi(arregloinstrucciones[a].rs);
				if(dir%4!=0){
			//		printf("%s\n","la direccion de memoria no es divisible de 4" );
					exit(1);
				}
				direccion=dir/4;
				for(int i=0 ; i < 1024; i++){

						memoria[direccion]=valores[dato1];
				}
				a++;

		}
		//INSTRUCCION BEQ
	else if(strcmp("beq",arregloinstrucciones[a].id)==0){

			inmediato=strtok(arregloinstrucciones[a].rt," \n");
			
			for (int i = 0; i < 32; i++){
				if(strcmp(arregloinstrucciones[a].rd,registros[i])==0){
					dato1=i;
				}
				 if(strcmp(arregloinstrucciones[a].rs,registros[i])==0){
					dato2=i;
				}
			}
			if(valores[dato1]==valores[dato2]){
				for(int i=0; i < lineas; i++){
					if(strcmp(inmediato,arregloinstrucciones[i].id)==0){
						arregloinstrucciones[a].verificador=1;

		//	printf("%d\n",arregloinstrucciones[a].verificador );
						posicion=i;
						break;
						}
					}
					a=posicion;
				}
				else{
					arregloinstrucciones[a].verificador=0;
		//	printf("%d\n",arregloinstrucciones[a].verificador );
					a++;
				}
		}
	else{
		a++;
	}


//printf("%s %s %s\n",arregloinstrucciones[a].id,arregloinstrucciones[a].rd,arregloinstrucciones[a].rs );
return a;
}
int lineas (char*entrada){
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
				valor2 	= strtok(NULL," ");
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
	return arreglo_registros;
}


char* unir_instruccion(char*id,char*rd,char*rs,char*rt){
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
	if(strcmp(EXMEM->rd,IDEX->rs)==0){
		return 1;
	}
	else if(strcmp(EXMEM->rd,IDEX->rt)==0){
		return 1;
	}
	else if(strcmp(MEMWB->rd,IDEX->rs)==0){
		return 1;
	}
	else if(strcmp(MEMWB->rd,IDEX->rt)==0){
		return 1;
	}
	else{
		return 0;
	}
}
void agregarNOP(pipeline* pipe){
	strcpy(pipe->linea[4],pipe->linea[3]);
	strcpy(pipe->linea[3],pipe->linea[2]);
	strcpy(pipe->linea[2],pipe->linea[1]);
	strcpy(pipe->linea[1],pipe->linea[0]);
	strcpy(pipe->linea[0],"NOP");
}
void escribir_pipeline(pipeline* pipe,char* aux){
	strcpy(pipe->linea[4],pipe->linea[3]);
	strcpy(pipe->linea[3],pipe->linea[2]);
	strcpy(pipe->linea[2],pipe->linea[1]);
	strcpy(pipe->linea[1],pipe->linea[0]);
	strcpy(pipe->linea[0],aux);
}
void mover_final(char** linea, char* aux){
	strcpy(linea[4],linea[3]);
	strcpy(linea[3],linea[4]);
	strcpy(linea[2],linea[1]);
	strcpy(linea[1],linea[0]);
	strcpy(linea[0],aux);
}
void salida1(FILE*salida,dato* arregloinstrucciones, int* arreglo_registros, int lineas){
		//lista enlazada para rescatar la traza
		lista* L;
		L=crearLista();
		//lista enlazada con los ciclos de pipeline
		lista_pipeline* pipe;
		pipe=crearlista_pipe();
		//buffers
		buffer* IFID = crearBuffer();
		buffer* IDEX = crearBuffer();
		buffer* EXMEM = crearBuffer();
		buffer* MEMWB = crearBuffer();
		dato* nodo;
		//LISTA CON LA TRAZA
			for(int i = 0; i < lineas; i=ejecutar(arregloinstrucciones,arreglo_registros,lineas,i,L)){
			nodo=crearnodo(arregloinstrucciones[i].id,arregloinstrucciones[i].rd,arregloinstrucciones[i].rs,arregloinstrucciones[i].rt,arregloinstrucciones[i].verificador);
			encolar(L,nodo);
			}
			//dejar la traza sin el NEXT
		eliminaretiquetas(L);
		//INICIO DE CODIGO [ [instruccion, rd, rs, rt], [], [] ...]
		char*** codigo;
		codigo=(char***)malloc(sizeof(char**)*lineas);
		for (int i = 0; i < lineas; ++i){
			codigo[i]=(char**)malloc(sizeof(char*)*5);
			for(int j=0; j < 5; j++){
				codigo[i][j]=(char*)malloc(sizeof(char));
			}
		}
		for (int i = 0; i < lineas; ++i)
		{
			strcpy(codigo[i][0],arregloinstrucciones[i].id);
			strcpy(codigo[i][1],arregloinstrucciones[i].rd);
			strcpy(codigo[i][2],arregloinstrucciones[i].rs);
			strcpy(codigo[i][3],arregloinstrucciones[i].rt);
		}
		//INICIO DE TRAZA [ [instruccion, rd, rs, rt], [], [] ...]
		char*** traza;
		traza=(char***)malloc(sizeof(char**)*lineas);
		for (int i = 0; i < lineas; ++i)
		{
			traza[i]=(char**)malloc(sizeof(char*)*5);
			for(int j=0; j < 5; j++){
				traza[i][j]=(char*)malloc(sizeof(char));
			}
		}
		int largo=largolista(L);
		for (int i = 0; i < largo ; i++){
			dato* elemento;
			elemento=buscar(L,i);
			strcpy(traza[i][0],elemento->id);
			strcpy(traza[i][1],elemento->rd);
			strcpy(traza[i][2],elemento->rs);
			strcpy(traza[i][3],elemento->rt);

		}

		//TRABAJO DE PIPELINE
		//primera linea:
		char* instruccion_aux;		
		instruccion_aux=unir_instruccion(traza[0][0],traza[0][1],traza[0][2],traza[0][3]);
		char** linea_aux;
		linea_aux = (char**)malloc(sizeof(char*)*5);
		for (int i = 0; i < 5; ++i)
		{
			linea_aux[i]=(char*)malloc(sizeof(char));
		}
		strcpy(linea_aux[0],instruccion_aux);
		strcpy(linea_aux[1],"-");
		strcpy(linea_aux[2],"-");
		strcpy(linea_aux[3],"-");
		strcpy(linea_aux[4],"-");
		pipeline* nodo_pipeline;
		nodo_pipeline=crearpipeline(linea_aux);
		encolar_pipe(pipe,nodo_pipeline);
		imprimirpipe(pipe);

		char* ins_completa;
		ins_completa=(char*)malloc(sizeof(char));
		//resto del pipeline:

		for (int i = 1; i < largo; i++){
		change_buffer(IFID,IDEX,EXMEM,MEMWB,traza[i][0],traza[i][1],traza[i][2],traza[i][3]);
		ins_completa=unir_instruccion(IDEX->id,IDEX->rd,IDEX->rs,IDEX->rt);
		//printf("%s %s %s %s || %s %s %s %s\n",traza[i][0],traza[i][1],traza[i][2],traza[i][3],codigo[i][0],codigo[i][1],codigo[i][2],codigo[i][3] );
		if(strcmp(IDEX->id,"add")==0 || strcmp(IDEX->id,"sub")==0 || strcmp(IDEX->id,"mul")==0 
		   || strcmp(IDEX->id,"div")==0|| strcmp(IDEX->id,"addi")==0 || strcmp(IDEX->id,"subi")==0){	
			
				int hazard;
				hazard=detectar_hazard(EXMEM,IDEX,MEMWB);
				if(hazard==1){

				escribir_pipeline(nodo_pipeline,ins_completa);
				agregarNOP(nodo_pipeline);
				i=i-1;
				encolar_pipe(pipe,nodo_pipeline);
				}

				else{

				escribir_pipeline(nodo_pipeline,ins_completa);
				encolar_pipe(pipe,nodo_pipeline);
		
				
				}
			}

		else if(strcmp(IDEX->id,"lw")==0 || strcmp(IDEX->id,"sw")==0){

			int hazard;
			hazard=detectar_hazard(EXMEM,IDEX,MEMWB);
				if(hazard==1){
				i=i-1;
				}
				else{
				i=i-1;
				}
		}

		else if(strcmp(IDEX->id,"beq")==0){
			
			if(strcmp(traza[i+1][0],codigo[i][0])==0 && strcmp(traza[i+1][1],codigo[i][1])==0
			&& strcmp(traza[i+1][2],codigo[i][2])==0 && strcmp(traza[i+1][3],codigo[i][3])==0){
				
			//printf("%s\n","no entra al beq" );
			int hazard;
			hazard=detectar_hazard(EXMEM,IDEX,MEMWB);
				if(hazard==1){
				//agregarNOP(nodo_pipeline);
				escribir_pipeline(nodo_pipeline,ins_completa);
				agregarNOP(nodo_pipeline);
				encolar_pipe(pipe,nodo_pipeline);
			//	printf("%s %s %s %s\n",nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3]);
				
				}
				else{
					//agregarNOP(nodo_pipeline);
					escribir_pipeline(nodo_pipeline,ins_completa);
					agregarNOP(nodo_pipeline);
					encolar_pipe(pipe,nodo_pipeline);
				}
				i=i-1;
				}

			else{
				//printf("%s\n","si entra al beq");
				int hazard;
			hazard=detectar_hazard(EXMEM,IDEX,MEMWB);
			if(hazard==1){
				//agregarNOP(nodo_pipeline);
				escribir_pipeline(nodo_pipeline,ins_completa);
				agregarNOP(nodo_pipeline);
				agregarNOP(nodo_pipeline);
				encolar_pipe(pipe,nodo_pipeline);
				//agregarNOP(nodo_pipeline);
			
			}
			else{
				//agregarNOP(nodo_pipeline);
				escribir_pipeline(nodo_pipeline,ins_completa);
				agregarNOP(nodo_pipeline);
				encolar_pipe(pipe,nodo_pipeline);
				
			}
			i=i-1;
			}
		}
		else if(strcmp(IDEX->id,"j")==0){
			//agregarNOP(nodo_pipeline);
			escribir_pipeline(nodo_pipeline,ins_completa);
			agregarNOP(nodo_pipeline);
			encolar_pipe(pipe,nodo_pipeline);
			i=i-1;
		}
	//	printf("%s %s %s %s\n",traza[i][0],traza[i][1],traza[i][2],traza[i][3]);
	//	printf("%s || %s || %s || %s || %s\n",nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
		encolar_pipe(pipe,nodo_pipeline);
	}

	for(int j=0; j<4;j++){
		char** ultimo;
		ultimo=pipe->fin->linea;
		//printf("%s\n", ultimo[0]);
		mover_final(ultimo,"-");
		//printf("%s || %s || %s || %s || %s\n",ultimo[0],ultimo[1],ultimo[2],ultimo[3],ultimo[4] );
	}
	imprimirpipe(pipe);
}