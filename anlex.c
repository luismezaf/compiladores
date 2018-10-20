/*
 *	Analizador Léxico
 *	Curso: Compiladores y Lenguajes de Bajo de Nivel
 *	Práctica de Programación Nro. 1
 *
 *	Descripcion:
 *	Implementa un analizador léxico que reconoce números, identificadores,
 * 	palabras reservadas, operadores y signos de puntuación para un lenguaje
 * 	con sintaxis tipo Pascal.
 *
 *	Alumno: Luis Meza
 */

/*********** Inclusión de cabecera **************/
#include "anlex.h"


/************* Variables globales **************/

int consumir;			/* 1 indica al analizador lexico que debe devolver
						el sgte componente lexico, 0 debe devolver el actual */

char cad[5*TAMLEX];		// string utilizado para cargar mensajes de error
token t;				// token global para recibir componentes del Analizador Lexico

// variables para el analizador lexico

FILE *archivo;			// Fuente pascal
char buff[2*TAMBUFF];	// Buffer para lectura de archivo fuente
char id[TAMLEX];		// Utilizado por el analizador lexico
int delantero=-1;		// Utilizado por el analizador lexico
int fin=0;				// Utilizado por el analizador lexico
int numLinea=1;			// Numero de Linea

/**************** Funciones **********************/


// Rutinas del analizador lexico

void error(const char* mensaje)
{
	printf("Lin %d: Error Lexico. %s.\n",numLinea,mensaje);
}

void sigLex()
{
	int i=0;
	char c=0;
	int acepto=0;
	int estado=0;
	char msg[41];
	entrada e;

	while((c=fgetc(archivo))!=EOF)
	{
        //printf("%c\n", c);
		if (c==' ' || c=='\t'){
            if(c==' ') printf(" ");
            else if (c=='\t') printf("\t");
			continue;	//eliminar espacios en blanco
        }
		else if(c=='\n')
		{
			//incrementar el numero de linea
			numLinea++;
			printf("\n");
			continue;
		}
		else if (isalpha(c))
		{
			//PR_TRUE || PR_FALSE || PR_NULL
			i=0;
			//Recoge y guarda la cadena en id[i]
			do{
				id[i]=c;
				i++;
				c=fgetc(archivo);
				if (i>=TAMLEX)
					error("Longitud de Identificador excede tamaño de buffer");
			}while(isalpha(c));
			// Agrega fin de linea
			id[i]='\0';
			// Si no es el final de archivo, retrocede un digito en el archivo
			if (c!=EOF)
				ungetc(c,archivo);
			else // Si es fin de linea
				c=0;

            if(strcmp(id, "false") || strcmp(id, "FALSE"))
            {
                strcpy(e.lexema,id);
                e.compLex=PR_FALSE;
                insertar(e);
                t.pe=buscar(id);
                t.compLex=PR_FALSE;
            }
            else if(strcmp(id, "true") || strcmp(id, "TRUE"))
            {
                strcpy(e.lexema,id);
                e.compLex=PR_TRUE;
                insertar(e);
                t.pe=buscar(id);
                t.compLex=PR_TRUE;
            }
            else if(strcmp(id, "null") || strcmp(id, "NULL"))
            {
                strcpy(e.lexema,id);
                e.compLex=PR_NULL;
                insertar(e);
                t.pe=buscar(id);
                t.compLex=PR_NULL;
            }

			break;
		}
		else if (c == '\"')
		{
			//LITERAL_CADENA
			i=0;
			//Recoge y guarda la cadena en id[i]
			do{
				id[i]=c;
				i++;
				c=fgetc(archivo);
				if (i>=TAMLEX)
					error("Longitud de Identificador excede tamaño de buffer");
			}while(isalpha(c) || isdigit(c) || c == '\"' || c == ' ');
			// Agrega fin de linea
			id[i]='\0';
			// Si no es el final de archivo, retrocede un digito en el archivo
			if (c!=EOF)
				ungetc(c,archivo);
			else // Si es fin de linea
				c=0;

			strcpy(e.lexema,id);
            e.compLex=LITERAL_CADENA;
            insertar(e);
            t.pe=buscar(id);
            t.compLex=LITERAL_CADENA;

			break;
		}
		else if (isdigit(c))
		{
				//es un LITERAL_NUM
				i=0;
				estado=0;
				acepto=0;
				id[i]=c;

				while(!acepto)
				{
					switch(estado){
					case 0: //una secuencia netamente de digitos, puede ocurrir . o e
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=0;
						}
						else if(c=='.'){
							id[++i]=c;
							estado=1;
						}
						else if(tolower(c)=='e'){
							id[++i]=c;
							estado=3;
						}
						else{
							estado=6;
						}
						break;

					case 1://un punto, debe seguir un digito (caso especial de array, puede venir otro punto)
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=2;
						}
						else{
							sprintf(msg,"No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 2://la fraccion decimal, pueden seguir los digitos o e
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=2;
						}
						else if(tolower(c)=='e')
						{
							id[++i]=c;
							estado=3;
						}
						else
							estado=6;
						break;
					case 3://una e, puede seguir +, - o una secuencia de digitos
						c=fgetc(archivo);
						if (c=='+' || c=='-')
						{
							id[++i]=c;
							estado=4;
						}
						else if(isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							sprintf(msg,"No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 4://necesariamente debe venir por lo menos un digito
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							sprintf(msg,"No se esperaba '%c'",c);
							estado=-1;
						}
						break;
					case 5://una secuencia de digitos correspondiente al exponente
						c=fgetc(archivo);
						if (isdigit(c))
						{
							id[++i]=c;
							estado=5;
						}
						else{
							estado=6;
						}break;
					case 6://estado de aceptacion, devolver el caracter correspondiente a otro componente lexico
						if (c!=EOF)
							ungetc(c,archivo);
						else
							c=0;
						id[++i]='\0';
						acepto=1;
						strcpy(e.lexema,id);
                        e.compLex=LITERAL_NUM;
                        insertar(e);
                        t.pe=buscar(id);
						t.compLex=LITERAL_NUM;
						break;
					case -1:
						if (c==EOF)
							error("No se esperaba el fin de archivo");
						else
							error(msg);
						exit(1);
					}
				}
			break;
		}
		else if (c=='[')
		{
			// L_CORCHETE
			//c=fgetc(archivo);
			t.compLex=L_CORCHETE;
            t.pe=buscar("[");
			break;
		}
		else if (c==']')
		{
			// R_CORCHETE
			//c=fgetc(archivo);
			t.compLex=R_CORCHETE;
            t.pe=buscar("]");
			break;
		}
		else if (c=='{')
		{
			// L_LLAVE
			//c=fgetc(archivo);
			t.compLex=L_LLAVE;
            t.pe=buscar("{");
			break;
		}
		else if (c=='}')
		{
			// R_LLAVE
			//c=fgetc(archivo);
			t.compLex=R_LLAVE;
            t.pe=buscar("}");
			break;
		}
		else if (c==',')
		{
			// COMA
			//c=fgetc(archivo);
			t.compLex=COMA;
            t.pe=buscar(",");
			break;
		}
		else if (c==':')
		{
			// DOS_PUTNOS
			//c=fgetc(archivo);
			t.compLex=DOS_PUTNOS;
            t.pe=buscar(":");
			break;
		}
		else if (c!=EOF)
		{
			sprintf(msg,"%c no esperado",c);
			error(msg);
		}
	}
	if (c==EOF)
	{
		t.compLex=EOF;
		// strcpy(e.lexema,"EOF");
		sprintf(e.lexema,"EOF");
		t.pe=&e;
	}

}

int main(int argc,char* args[])
{
	// inicializar analizador lexico

	initTabla();
	initTablaSimbolos();

	if(argc > 1)
	{
		if (!(archivo=fopen(args[1],"rt")))
		{
			printf("Archivo no encontrado.\n");
			exit(1);
		}
		while (t.compLex!=EOF){
			sigLex();
			printf("%s ", numToCompLex(t.compLex));
			//printf("Lin %d: %s -> %d\n",numLinea,t.pe->lexema,t.compLex);
		}
		fclose(archivo);
	}else{
		printf("Debe pasar como parametro el path al archivo fuente.\n");
		exit(1);
	}

	return 0;
}

char* numToCompLex(int num){
    switch(num)
    {
        case 256:
         return "L_CORCHETE";
        case 257:
         return "R_CORCHETE";
        case 258:
         return "L_LLAVE";
        case 259:
         return "R_LLAVE";
        case 260:
         return "COMA";
        case 261:
         return "DOS_PUTNOS";
        case 262:
         return "STRING";
        case 263:
         return "NUMBER";
        case 264:
         return "PR_TRUE";
        case 265:
         return "PR_FALSE";
        case 266:
         return "PR_NULL";
    }
    return NULL;
}
