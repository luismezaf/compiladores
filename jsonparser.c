#include "ansin.h"

int main(int argc,char* args[])
{
	// inicializar analizador lexico

	FILE *archivo = NULL;

	initTabla();
	initTablaSimbolos();

	if(argc > 1)
	{
		if (!(archivo=fopen(args[1],"rt")))
		{
			printf("Archivo no encontrado.\n");
			exit(1);
		}
		initanlex(archivo);
	        initansin(getListTokens());
		fclose(archivo);
	}else{
		printf("Debe pasar como parametro el path al archivo fuente.\n");
		exit(1);
	}

	return 0;
}
