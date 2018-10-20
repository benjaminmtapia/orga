#include <math.h>
#include "struct.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
	char* nombreArchivo;
	int tamanoDatos;
	int PalabrasPorBloque;
	int c;
	while( (c = getopt(argc, argv, "n:m:p:")) != -1){
      switch(c){
        case 'n':
          nombreArchivo = optarg;
          break;
        case 'm':
          tamanoDatos = atoi(optarg);
          break;
        case 'p':
          PalabrasPorBloque = atoi(optarg);
          break;
        case '?':
          printf("Opción desconocida: %c\n",c);
        default:
          printf("parametros mal ingresados\n");
          return 1;
      }
  }

	posiblesCache(PalabrasPorBloque,tamanoDatos,nombreArchivo);
	return 0;
}