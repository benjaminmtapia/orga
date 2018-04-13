#include "funciones.h"

void procesar(dato* arregloinstrucciones, int lineas, int valores[32],char senal[10],FILE*salida, FILE*salida2){

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
	int a=0;
	for (a = 0; a < lineas; a++){
		//INSTRUCCION JUMP
		if(strcmp("j",arregloinstrucciones[a].id)==0){
			int indice=0;
			inmediato=strtok(arregloinstrucciones[a].r1," \n");
			if(senal[1]!='0'){
				fprintf(salida2, "%s %s\n",arregloinstrucciones[a].id,inmediato);
				fprintf(salida, "%s %s,",arregloinstrucciones[a].id,inmediato );
				for(int i=0; i < lineas; i++){
					if(strcmp(inmediato,arregloinstrucciones[i].id)==0){
						indice=i;
						break;
					}
				}
				a=indice;
				for (int i = 0; i < 32; ++i)
				{
					fprintf(salida, "%d,", valores[i]);
				}
				fprintf(salida, "\n");
			}
		}
		//INSTRUCCIONES ADD,SUB,MUL,DIV
		else if(strcmp("add",arregloinstrucciones[a].id)==0 || strcmp("sub",arregloinstrucciones[a].id)==0 ||
			strcmp("mul",arregloinstrucciones[a].id)==0 || strcmp("div",arregloinstrucciones[a].id)==0){
			inmediato=strtok(arregloinstrucciones[a].r3," \n");
			fprintf(salida, "%s %s %s %s ,", arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,arregloinstrucciones[a].r3);
			if(senal[8]!='0' || senal[5]!='0'){
			for(int i=0; i < 32; i++){
				if(strcmp(arregloinstrucciones[a].r1,registros[i])==0){
				dato1=i;
				}
				 if(strcmp(arregloinstrucciones[a].r2,registros[i])==0){
				dato2=i;
				}
				 if(strcmp(arregloinstrucciones[a].r3,registros[i])==0){
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
			for (int i = 0; i < 32; i++){
				fprintf(salida, "%d,", valores[i]);
			}
				fprintf(salida, "\n" );
				fprintf(salida2, "%s %s %s %s\n",arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,arregloinstrucciones[a].r3 );
				}

		}
		//INSTRUCCIONES ADDI Y SUBI
		else if(strcmp("addi",arregloinstrucciones[a].id)==0 || strcmp("subi",arregloinstrucciones[a].id)==0){
			if (senal[8]!='0'){
			inmediato=strtok(arregloinstrucciones[a].r3," \n");
			inmediate=atoi(inmediato);
			fprintf(salida, "%s %s %s %s ,", arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,inmediato);
			for (int i = 0; i < 32; i++){
				if(strcmp(arregloinstrucciones[a].r1,registros[i])==0){
					dato1=i;
				}
				 if(strcmp(arregloinstrucciones[a].r2,registros[i])==0){
					dato2=i;
				}
			}
			
				if(strcmp("addi",arregloinstrucciones[a].id)==0){
					valores[dato1]=valores[dato2]+inmediate;
				}
				else{
					valores[dato1]=valores[dato2]-inmediate;
				}
				for (int i = 0; i < 32; i++){
				fprintf(salida, "%d,",valores[i] );
				}
				fprintf(salida, "\n" );
				fprintf(salida2, "%s %s %s %s\n",arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,inmediato);
			}
		}
		//INSTRUCCIONES LW Y SW
		else if(strcmp("lw",arregloinstrucciones[a].id)==0 || strcmp("sw",arregloinstrucciones[a].id)==0){
			if(senal[3]!='0'){
				fprintf(salida, "%s %s %s(%s) ,", arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,arregloinstrucciones[a].r3);
				for(int i=0; i < 32; i++){
					if(strcmp(arregloinstrucciones[a].r1,registros[i])==0){
					dato1=i;
					
				}
				else if(strcmp(arregloinstrucciones[a].r3,registros[i])==0){
					dato3=i;
						}
					}
				int dir=atoi(arregloinstrucciones[a].r2);
				if(dir%4!=0){
					printf("%s\n","la direccion de memoria no es divisible de 4" );
					exit(1);
				}
				direccion=dir/4;
				for(int i=0 ; i < 1024; i++){
					if(strcmp("lw",arregloinstrucciones[a].id)==0 ){
						valores[dato1]=memoria[direccion];
					}
					else{
						memoria[direccion]=valores[dato1];
					}
				}
				for(int i=0; i < 32; i++){
					fprintf(salida, "%d,", valores[i]);
				}
					fprintf(salida, "\n" );
					fprintf(salida2, "%s %s %s(%s)\n",arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,arregloinstrucciones[a].r3 );
					}
		}
		//INSTRUCCION BEQ
		else if(strcmp("beq",arregloinstrucciones[a].id)==0){
			if(senal[2]!='0' || senal[8]!='0'){
			posicion=0;
			inmediato=strtok(arregloinstrucciones[a].r3," \n");
			fprintf(salida2, "%s %s %s %s\n",arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,arregloinstrucciones[a].r3 );
			fprintf(salida, "%s %s %s %s,", arregloinstrucciones[a].id,arregloinstrucciones[a].r1,arregloinstrucciones[a].r2,inmediato);
			for(int i=0; i < 32; i++){
				if(strcmp(arregloinstrucciones[a].r1,registros[i])==0){
				dato1=i;
				}
				if(strcmp(arregloinstrucciones[a].r2,registros[i])==0){
				dato2=i;
				}
				if(valores[dato1]==valores[dato2]){
				for(int i=0; i < lineas; i++){
					if(strcmp(inmediato,arregloinstrucciones[i].id)==0){
						posicion=i;
						break;
						}
					}

				a=posicion;
				}
			}
			for (int i = 0; i < 32; i++){
				fprintf(salida, "%d,", valores[i]);
			}
				fprintf(salida, "\n" );
		}
	}

	}
}
char* leerarchivo2(char* entrada2, char senal[10]){
	//char senal[10];
	char a;
	int i=0;
	FILE* archivo;
	char*valor; char*valor2;
	char buffer[25*100];
	archivo=fopen(entrada2,"r");
	int cont=0;

		if(archivo==NULL){
		printf("%s\n","Falló apertura de archivo de señales" );
		exit(1);
		}

		while(!feof(archivo)){
		fgets(buffer, 25*100, archivo);
		cont++;
		
		}
	fclose(archivo);
	archivo=fopen(entrada2,"r");
	char (*instrucciones[10])[8][4];

		while(!feof(archivo) && i<cont){
		//SE SEPARA LA LINEA POR UN ESPACIO Y SE CONSERVA SOLO LA SEÑAL
		fgets(buffer, 25*100, archivo);
		valor 	= strtok(buffer, " ");
		valor2 	= strtok(NULL," ");
		a=valor2[0];
		senal[i]=a;
		i++;
		}
	fclose(archivo);
	return senal;
}

void leerarchivo(char* entrada, char senal[10],FILE* salida,FILE*salida2){
	FILE* archivo;
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

	int valores[32];
	for (int i = 0; i < 32; ++i){ valores[i]=0; }
	int aux=0;

	dato* arregloinstrucciones;
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
				strcpy(arregloinstrucciones[aux].r1,valor2);
				valor3 	= strtok(NULL,", ");
				strcpy(arregloinstrucciones[aux].r2,valor3);
				valor4	= strtok(NULL," ");
				strcpy(arregloinstrucciones[aux].r3,valor4);
		}
		else if(strcmp(valor,"j")==0){
				strcpy(arregloinstrucciones[aux].id,valor);
				valor2 	= strtok(NULL," ");
				strcpy(arregloinstrucciones[aux].r1,valor2);
		}
		
		else if(strcmp(valor,"lw")==0 || strcmp(valor,"sw")==0){
				strcpy(arregloinstrucciones[aux].id,valor);
				valor2 	= strtok(NULL,", ");
				strcpy(arregloinstrucciones[aux].r1,valor2);
				valor3 	= strtok(NULL," (");
				strcpy(arregloinstrucciones[aux].r2,valor3);
				valor4	= strtok(NULL,")");
				strcpy(arregloinstrucciones[aux].r3,valor4);
		}
		else{
			valor=strtok(valor,":");
			strcpy(arregloinstrucciones[aux].id,valor);
		}
		
	aux++;
}
procesar(arregloinstrucciones,lineas,valores,senal,salida,salida2);
free(arregloinstrucciones);
	fclose(archivo);
}
void cabecera(FILE* salida){
	char*registros[32]={"$zero","$at","$v0","$v1","$a0",
	"$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5",
	"$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6",
	"$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

	fprintf(salida,  "Ciclo,");
	fprintf(salida, "$zero,$at,$v0,$v1,");
	fprintf(salida, "$a0,$a1,$a2,$a3,");
	fprintf(salida,  "$t0,$t1,$t2,$t3,$t4,$t5,$t6,$t7,");
	fprintf(salida, "$s0,$s1,$s2,$s3,$s4,$s5,$s6,$s7,");
	fprintf(salida,  "$t8,$t9,");
	fprintf(salida, "$k0,$k1,$gp,$sp,$fp,$ra\n");
}
int main(int argc, char const *argv[]){

FILE* salida;
FILE* salida2;
char archivosalida[20];
char archivosalida2[20];
char archivoentrada[20];
char archivoentrada2[20];

//NOMBRES DE ARCHIVOS DE ENTRADA Y SALIDA
printf("%s\n","Ingrese archivo con las instrucciones" );
scanf("%s",archivoentrada);
printf("%s\n","Ingrese archivo con las señales" );
scanf("%s",archivoentrada2);
printf("%s\n","Ingrese archivo para la traza" );
scanf("%s",archivosalida);
printf("%s\n","Ingrese archivo .csv para escribir los registros" );
scanf("%s",archivosalida2);


salida=fopen(archivosalida2,"w");
salida2=fopen(archivosalida,"w");
if(salida==NULL || salida2==NULL){
	printf("%s\n","Error de archivo" );
	exit(1);
}
fprintf(salida2, "%s\n", "");
char senal[10];
char* senales;
cabecera(salida);
senales=leerarchivo2(archivoentrada2,senal);
leerarchivo(archivoentrada,senal,salida,salida2);
fclose(salida);
fclose(salida2);
return 0;

}