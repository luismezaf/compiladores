#include "ansin.h"

listatokens *listt;

void initansin(listatokens *lt){

	listt = lt;

	if(listt == NULL){
		printf("No se encuentra la lista de Tokens, es posible que el análisis lexico no se haya realizado.");
		exit(1);
	}
	//printf("\nAnalizador sintactico iniciado\n");
	//printListTokens(lt);
	p_json();
}


void p_att_value() {

	if(getToken(listt).compLex == L_CORCHETE || getToken(listt).compLex == L_LLAVE)
		p_element();
	else if(getToken(listt).compLex == LITERAL_CADENA)
		match(LITERAL_CADENA);
	else if(getToken(listt).compLex == LITERAL_NUM)
		match(LITERAL_NUM);
	else if(getToken(listt).compLex == PR_TRUE)
		match(PR_TRUE);
	else if(getToken(listt).compLex == PR_FALSE)
		match(PR_FALSE);
	else if(getToken(listt).compLex == PR_NULL)
		match(PR_NULL);
	else{
		sintError("[, {, String, Numeric, true, false o null");
	}
}

void p_att_name() {
	if(getToken(listt).compLex == LITERAL_CADENA){
		match(LITERAL_CADENA);
	}
}

void p_alp() {
	if(getToken(listt).compLex == COMA){
		match(COMA);
		p_attribute();
		p_alp();
	}
}

void p_attribute() {
	if(getToken(listt).compLex == LITERAL_CADENA){
		p_att_name();
		match(DOS_PUTNOS);
		p_att_value();
	}
	else{
		sintError("String");
	}
}

void p_attr_list(){
	if(getToken(listt).compLex == LITERAL_CADENA){
		p_attribute();
		p_alp();
	}
	else{
		sintError("String");
	}
}

void p_ep() {
	if(getToken(listt).compLex == COMA){
		match(COMA);
		p_element();
		p_ep();
	}
}

void p_element_list() {
	if(getToken(listt).compLex == L_CORCHETE || getToken(listt).compLex == L_LLAVE){
		p_element();
		p_ep();
	}
	else{
		sintError("[ o {");
	}
}

void p_ap(){
	if(getToken(listt).compLex == L_CORCHETE || getToken(listt).compLex == L_LLAVE){
		p_element_list();
		match(R_CORCHETE);
	}
	else if(getToken(listt).compLex == R_CORCHETE){
		match(R_CORCHETE);
	}
	else{
		sintError("[, { o ]");
	}
}

void p_op(){
	if(getToken(listt).compLex == LITERAL_CADENA){
		p_attr_list();
		match(R_LLAVE);
	}
	else if(getToken(listt).compLex == R_LLAVE){
		match(R_LLAVE);
	}
	else{
		sintError("String o }");
	}
}

void p_array(){
	if(getToken(listt).compLex == L_CORCHETE){
		match(L_CORCHETE);
		p_ap();
	}
	else{
		sintError("[");
	}
}

void p_object(){
	if(getToken(listt).compLex == L_LLAVE){
		match(L_LLAVE);
		p_op();
	}
	else{
		sintError("{");
	}
}

void p_element(){
	if(getToken(listt).compLex == L_LLAVE){
		p_object();
	}
	else if(getToken(listt).compLex == L_CORCHETE){
		p_array();
	}
	else{
		sintError("{ o [");
	}
}

void p_json(){
	p_element();
}

void match(int expToken){
	if(getToken(listt).compLex == expToken){
		removeToken(listt);
	}
	else{
		sintError(numToLexema(expToken));
	}
}

void sintError(char* expTok){
	token curtok = getToken(listt);
	//char *expected = numToCompLex(curtok.compLex);
	char *expected = numToLexema(curtok.compLex);
	//char *expected2 = (char *)expected;
	printf("Lin %d, Col %d. Error Sintactico. Se esperaba %s, se encontro %s\n", curtok.line, curtok.column, expTok, expected);
	exit(1);
}

char *numToLexema(int num){
    switch(num)
    {
        case 256:
         return "[";
        case 257:
         return "]";
        case 258:
         return "{";
        case 259:
         return "}";
        case 260:
         return ",";
        case 261:
         return ":";
        case 262:
         return "String";
        case 263:
         return "Number";
        case 264:
         return "true";
        case 265:
         return "false";
        case 266:
         return "null";
        case 267:
         return "un elemento desconocido.";

    }
    return NULL;
}

