#include "funciones.h"

int ejecutar(dato* arregloinstrucciones,int* valores, int lineas, int a, lista*L){
	//funcion que ejecuta una instruccion de mips e inserta la traza en una lista, retornando a su vez el indice en que quedo
	//luego de ejecutar cada instruccion. Esta funcion puede ir ejecutando el valor de los registros
	//entrada: codigo mips en arreglo de estructuras, arreglo de enteros con los valores de registros, cantidad de lineas del codigo, indice a buscar, lista a insertar
	//salida: indice en el que se desarrollo la ultima instruccion y va encolando la traza a la lista L
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
						posicion=i;
						break;
					}
				}
				a=posicion;
			
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

						posicion=i;
						break;
						}
					}
					a=posicion;
				}
				else{
					arregloinstrucciones[a].verificador=0;
					a++;
				}
		}
	else{
		a++;
	}


//printf("%s %s %s\n",arregloinstrucciones[a].id,arregloinstrucciones[a].rd,arregloinstrucciones[a].rs );
return a;
}

char*** arreglo_codigo(dato*arregloinstrucciones, int lineas){
	//a partir de un arreglo con las instrucciones mips, realiza un arreglo triple puntero
	//donde cada elemento es una instruccion mips separada por instruccion, y sus 3 registros
	//representacion = [ [instruccion,registro1,registro2,registro3] , [instruccion,r1,r2,r3], ...]
	//entrada: arreglo de instrucciones mips y cantidad de lineas
	//salida: arreglo de strings con el codigo
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
		return codigo;
}

char*** arreglo_traza(lista*L, int largo, int lineas){
	//convierte la traza del codigo (en caso de haber saltos) en un arreglo char*** al igual que la funcion arreglo_codigo
	//entrada: una lista enlazada con la traza, el largo de la lista enlazada y las lineas del codigo original
	//salida: arreglo de strings con las instrucciones que se ejecutan en el codigo mips
	char*** traza;
		traza=(char***)malloc(sizeof(char**)*lineas);
		for (int i = 0; i < lineas; ++i)
		{
			traza[i]=(char**)malloc(sizeof(char*)*5);
			for(int j=0; j < 5; j++){
				traza[i][j]=(char*)malloc(sizeof(char));
			}
		}
		//int largo=largolista(L);
		for (int i = 0; i < largo ; i++){
			dato* elemento;
			elemento=buscar(L,i);
			strcpy(traza[i][0],elemento->id);
			strcpy(traza[i][1],elemento->rd);
			strcpy(traza[i][2],elemento->rs);
			strcpy(traza[i][3],elemento->rt);

		}
	return traza;
}
void salida1(FILE*salida,FILE* salida2,dato* arregloinstrucciones, int* arreglo_registros, int lineas){
	//ejecucion de pipeline y hazards de datos y control, se comentan los procesos a lo largo de la funcion
	//entrada: archivos de salida, codigo mips en arreglo de estructuras, arreglo con los valores de los 32 registros, cantidad de lineas del codigo
	//salida: no retorna un valor como funcion, pero escribe en los archivos de salida el pipeline y los h
	//	salida=fopen("S1.csv","w");
	//	salida2=fopen("S2.csv","w");

	//se imprimen las cabeceras de los archivos de salida
		fprintf(salida,"%s;%s;%s;%s;%s;%s\n","CICLO","IF","ID","EX","MEM","WB");
		fprintf(salida2,"%s;%s;%s\n","CICLO","Datos","Control");
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

		//INICIO DE TRAZA Y CODIGO*** [ [instruccion, rd, rs, rt], [], [] ...]
			char*** codigo;
			codigo=arreglo_codigo(arregloinstrucciones,lineas);
			char*** traza;
			int largo=largolista(L);
			traza=arreglo_traza(L,largo,lineas);

		//TRABAJO DE PIPELINE
		//primera linea: debido a que se necesita tener al menos un elemento cargado en el pipeline en el primer ciclo
			char* instruccion_aux;		
			instruccion_aux=unir_instruccion(traza[0][0],traza[0][1],traza[0][2],traza[0][3]);
			char** linea_aux;
			linea_aux = (char**)malloc(sizeof(char*)*5);
			for (int i = 0; i < 5; ++i){
			linea_aux[i]=(char*)malloc(sizeof(char));}

			strcpy(linea_aux[0],instruccion_aux);
			strcpy(linea_aux[1],"-");
			strcpy(linea_aux[2],"-");
			strcpy(linea_aux[3],"-");
			strcpy(linea_aux[4],"-");
		//se encola la linea en el pipeline y se escribe en el archivo
			pipeline* nodo_pipeline;
			nodo_pipeline=crearpipeline(linea_aux);
			fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",1,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
			fprintf(salida2, "%d;%s ; %s\n",1,"-","-" );
			encolar_pipe(pipe,nodo_pipeline);
			char* ins_completa;
			ins_completa=(char*)malloc(sizeof(char));
		//resto del pipeline:
			int ciclo;
			int hazard;
			ciclo=2;
		for (int i = 1; i < largo; i++){
			//se hace push a los buffers, se toma la instruccion actual de la traza, y se verifican los hazards
			change_buffer(IFID,IDEX,EXMEM,MEMWB,traza[i][0],traza[i][1],traza[i][2],traza[i][3]);
			ins_completa=unir_instruccion(traza[i][0],traza[i][1],traza[i][2],traza[i][3]);
			hazard=detectar_hazard(EXMEM,IDEX,MEMWB);
			

			if(strcmp(IDEX->id,"add")==0 || strcmp(IDEX->id,"sub")==0 || strcmp(IDEX->id,"mul")==0 || 
				strcmp(IDEX->id,"div")==0 || strcmp(IDEX->id,"sw")==0 || strcmp(IDEX->id,"addi")==0 || 
				strcmp(IDEX->id,"subi")==0){

				if(hazard==1){
					//si es que hay hazards:
				//	agregarNOP(nodo_pipeline);
					escribir_pipeline(nodo_pipeline,ins_completa);
					fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
					fprintf(salida2, "%d;%s ; %s\n",ciclo,IDEX->rd,"-" );

					//i=i-1;
					}
				else{

					escribir_pipeline(nodo_pipeline,ins_completa);
					fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","-" );
					fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
					//i=i-1;
					}
					ciclo++;
				//escribir_pipeline(nodo_pipeline,ins_completa);
				//fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
				
				}
			else if(strcmp(IDEX->id,"lw")==0){
				
					if(hazard==1){
					fprintf(salida2, "%d;%s ; %s\n",ciclo,IDEX->rd,"-" );
					agregarNOP(nodo_pipeline);
					escribir_pipeline(nodo_pipeline,ins_completa);
					fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
					i=i-1;
					}
					else{
					fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","-" );
					fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
					//i=i-1;
					}
					ciclo++;
				
			}
			//INSTRUCCION BEQ
			else if(strcmp(IDEX->id,"beq")==0){
				pipeline* nodo_aux;
				nodo_aux = nodo_pipeline;
				char* comparador;
				comparador = (char*) malloc(sizeof(char));
				comparador=strtok(codigo[i-1][3]," ");
				//se verifica si hubo salto o no
				if(strcmp(codigo[i-1][3],traza[i][0])==0 ){
					//en caso de que salte:

					char* auxiliar;char*auxiliar2;char*auxiliar3;

					auxiliar = (char*)malloc(sizeof(char));
					auxiliar2 = (char*)malloc(sizeof(char));
					auxiliar3 = (char*)malloc(sizeof(char));
					//cargamos la instrucciones que siguen del codigo (bajo el beq)
					auxiliar=unir_instruccion(codigo[i][0],codigo[i][1],codigo[i][2],codigo[i][3]);	
					auxiliar2=unir_instruccion(traza[i+1][0],traza[i+1][1],traza[i+1][2],traza[i+1][3]);

					//cargo instruccion que viene debajo de beq
					printf("%s %s %s %s %s \n",nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4] );
					escribir_pipeline(nodo_aux,auxiliar);
					fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4]);
					//cargo el nop
					printf("%s %s %s %s %s \n",nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4] );
					
					ciclo++;
					corregirNodo(nodo_aux,auxiliar);
					
					//cargo despues de la etiqueta
					escribir_pipeline(nodo_aux,auxiliar2);
					printf("ABAJO ETIQUETA-> %s %s %s %s %s \n",nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4] );
					fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4]);
					fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","Hazard salto" );
					ciclo++;
					strcpy(nodo_pipeline->linea[1],"NOP");
					printf("%s %s %s %s \n",nodo_pipeline->linea[0] ,nodo_pipeline->linea[1] ,nodo_pipeline->linea[2] ,nodo_pipeline->linea[3] );
					i=i+1;
				}

					else{
						//EN CASO DE QUE NO SALTE
						//se cargan una bajo el beq y dos bajo la etiqueta
						nodo_aux=nodo_pipeline;
						char* auxiliar;char*auxiliar2;char*auxiliar3;char* etiqueta;
						int indiceEtiqueta;
						auxiliar = (char*)malloc(sizeof(char));
						auxiliar2 = (char*)malloc(sizeof(char));
						auxiliar3 = (char*)malloc(sizeof(char));
						
						indiceEtiqueta=buscador(codigo,largo);
						//instrucciones bajo la etiqueta
						for (int i = 0; i < largo; ++i){
							if(indiceEtiqueta+1 <largo){
								auxiliar=unir_instruccion(codigo[indiceEtiqueta+1][0],codigo[indiceEtiqueta+1][1],codigo[indiceEtiqueta+1][2],codigo[indiceEtiqueta+1][3]);								
							}
							if(indiceEtiqueta+2 < largo){
								auxiliar2=unir_instruccion(codigo[indiceEtiqueta+2][0],codigo[indiceEtiqueta+2][1],codigo[indiceEtiqueta+2][2],codigo[indiceEtiqueta+2][3]);								
							}
							else{
								//cargo instruccion 1 no mas
								auxiliar2=unir_instruccion(codigo[indiceEtiqueta+1][0],codigo[indiceEtiqueta+1][1],codigo[indiceEtiqueta+1][2],codigo[indiceEtiqueta+1][3]);								
							}
						}
						auxiliar3=unir_instruccion(codigo[i][0],codigo[i][1],codigo[i][2],codigo[i][3]);
						fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","Hazard BEQ" );
						//carga instruccion bajo beq
						escribir_pipeline(nodo_aux,auxiliar3);
					//	printf("BAJO BEQ %s %s %s %s %s\n",nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4] );
						fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4]);
						ciclo++;
						//se converite a NOP la instruccion anterior y se carga una bajo la etiqueta
						corregirNodo(nodo_aux,auxiliar3);
						escribir_pipeline(nodo_aux,auxiliar);

						fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4]);
						fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","Hazard prediccion" );
						ciclo++;
						//se carga otra instruccion bajo la etiqueta
						escribir_pipeline(nodo_aux,auxiliar2);
						fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4]);
						fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","Hazard prediccion" );
						ciclo++;
						fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","-" );
						//convertimos las dos de la etiqueta en NOP y cargamos la instruccion bajo el beq
						corregirNodo(nodo_aux,auxiliar);
						corregirNodo(nodo_aux,auxiliar2);
						escribir_pipeline(nodo_aux,auxiliar3);
						fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_aux->linea[0],nodo_aux->linea[1],nodo_aux->linea[2],nodo_aux->linea[3],nodo_aux->linea[4]);
						
						ciclo++;
						nodo_pipeline=nodo_aux;
				} 
			}

			else if(strcmp(IDEX->id,"j")==0){
						//se buscan las instrucciones bajo la etiqueta y bajo el codigo
						char* auxiliar;char*auxiliar2;char*auxiliar3;char* etiqueta;
						int indiceEtiqueta;
						auxiliar = (char*)malloc(sizeof(char));
						auxiliar2 = (char*)malloc(sizeof(char));
						auxiliar3 = (char*)malloc(sizeof(char));
						indiceEtiqueta=buscador(codigo,largo);
						auxiliar = unir_instruccion(codigo[i][0],codigo[i][1],codigo[i][2],codigo[i][3]);
						//cargo la que esta abajo del codigo
						escribir_pipeline(nodo_pipeline,auxiliar);
						fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
						ciclo++;
						corregirNodo(nodo_pipeline,auxiliar);
						i++;
			}
	
			else{
				fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","-" );
				escribir_pipeline(nodo_pipeline,ins_completa);
				fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
				ciclo++;
			}
			//fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,nodo_pipeline->linea[0],nodo_pipeline->linea[1],nodo_pipeline->linea[2],nodo_pipeline->linea[3],nodo_pipeline->linea[4]);
			//ciclo++;

	}
	//para la ultima instruccion, se corre la linea
	for(int j=0; j<4;j++){
		fprintf(salida2, "%d;%s ; %s\n",ciclo,"-","-" );
		char** ultimo;
		ultimo=pipe->fin->linea;
		mover_final(ultimo,"-");
		fprintf(salida,"%d; %s ; %s ; %s ; %s ; %s\n",ciclo,ultimo[0],ultimo[1],ultimo[2],ultimo[3],ultimo[4] );
		ciclo++;
	}

}