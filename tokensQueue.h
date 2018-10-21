#include "anlex.h"

typedef struct nt{
	token tok;
	struct nt *sig;
} nodetoken;

typedef struct{
	nodetoken *first;
	nodetoken *last;
} listatokens;

listatokens *getListTokens();
void addTokenToQueue(listatokens *listt, token t);
void printListTokens(listatokens *listt);
token getToken(listatokens *listt);
void removeToken(listatokens *listt);
