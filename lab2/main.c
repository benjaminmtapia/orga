#include "funciones.h"
int main(int argc, char const *argv[]){

FILE* salida;
FILE* salida2;
char archivosalida[20];
char archivosalida2[20];
char archivosalida3[20];
char archivoentrada[20];
char archivoentrada2[20];

//NOMBRES DE ARCHIVOS DE ENTRADA Y SALIDA
printf("%s\n","Ingrese archivo con las instrucciones" );
scanf("%s",archivoentrada);
printf("%s\n","Ingrese archivo con los valores de los registros" );
scanf("%s",archivoentrada2);
printf("%s\n","Ingrese archivo para el pipeline (incluya extension)" );
scanf("%s",archivosalida);
printf("%s\n","Ingrese archivo para los hazards (incluya extension)" );
scanf("%s",archivosalida2);

salida=fopen(archivosalida,"w");
salida2=fopen(archivosalida2,"w");
//salida3=fopen(archivosalida3,"w");

if(salida==NULL || salida2==NULL ){
	printf("%s\n","Error de archivo" );
	exit(1);
}


dato* arregloinstrucciones;
int* arreglo_registros;
arregloinstrucciones = leerarchivo(archivoentrada,arregloinstrucciones);
int largo;
largo=lineas(archivoentrada);

arreglo_registros=leerarchivo2(archivoentrada2,arreglo_registros);

salida1(salida,salida2,arregloinstrucciones,arreglo_registros,largo);
fclose(salida);
fclose(salida2);
free(arregloinstrucciones);
free(arreglo_registros);
return 0;

}