/*********** Librerias utilizadas **************/
#include "heads.h"

/************* Definiciones ********************/

//Codigos
#define L_CORCHETE		256
#define R_CORCHETE		257
#define L_LLAVE			258
#define R_LLAVE 		259
#define COMA    		260
#define DOS_PUTNOS		261
#define LITERAL_CADENA		262
#define LITERAL_NUM		263
#define PR_TRUE 		264
#define PR_FALSE		265
#define PR_NULL			266
#define UNKNOW			267
// Fin Codigos
#define TAMBUFF 	5
#define TAMLEX 		50
#define TAMHASH 	101

/************* Estructuras ********************/

typedef struct entrada{
	//definir los campos de 1 entrada de la tabla de simbolos
	int compLex;
	char lexema[TAMLEX];
} entrada;

typedef struct {
	int compLex;
	int line;
	int column;
	entrada *pe;
} token;


/************* Prototipos ********************/
void insertar(entrada e);
entrada* buscar(const char *clave);
void initTabla();
void initTablaSimbolos();
void sigLex();
char* numToCompLex(int num);
void printsomething();
int initanlex(FILE *arch);
int chlistCompare(char chlist[], const char string[]);

