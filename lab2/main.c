#include "funciones.h"
int main(int argc, char const *argv[]){

FILE* salida;
//FILE* salida2;
char archivosalida[20];
char archivosalida2[20];
char archivosalida3[20];
char archivoentrada[20];
char archivoentrada2[20];
/*
//NOMBRES DE ARCHIVOS DE ENTRADA Y SALIDA
printf("%s\n","Ingrese archivo con las instrucciones" );
scanf("%s",archivoentrada);
printf("%s\n","Ingrese archivo con las señales" );
scanf("%s",archivoentrada2);
printf("%s\n","Ingrese archivo para la traza" );
scanf("%s",archivosalida);
printf("%s\n","Ingrese archivo .csv para escribir los registros" );
scanf("%s",archivosalida2);
printf("%s\n","Ingrese archivo .csv para escribir los registros" );
scanf("%s",archivosalida3);

salida2=fopen(archivosalida,"w");
salida=fopen(archivosalida2,"w");
salida3=fopen(archivosalida3,"w");

if(salida==NULL || salida2==NULL || salida3==NULL){
	printf("%s\n","Error de archivo" );
	exit(1);
}
*/

dato* arregloinstrucciones;
int* arreglo_registros;
arregloinstrucciones = leerarchivo("M1.asm",arregloinstrucciones);
int largo;
largo=lineas(archivoentrada);

arreglo_registros=leerarchivo2("M2.asm",arreglo_registros);

salida1(salida,arregloinstrucciones,arreglo_registros,largo);
//salida2(salida,arregloinstrucciones,arreglo_registros,largo);
return 0;

}