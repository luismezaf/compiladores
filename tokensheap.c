#include "tokensheap.h"

void addTokenToQueue(listatokens listt, token t){
	if(listt->first == NULL){
		nodetoken *nt = malloc(sizeof(nodetoken));
		nt->tok = t;
		nt->sig = NULL;
		listt->first = nt;
		listt->last = listt->first;
	}
	else{
		nodetoken *nt = malloc(sizeof(nodetoken));
		nt->tok = t;
		nt->sig = NULL;
		listt->last->sig = nt;
		listt->last = nt;
	}
}

void printListTokens(listatokens listt){
	nodetoken *node = listt->first;

	while(node != NULL){
		token tok = node->tok;
		printf("%s, ", numToCompLex(tok.compLex));
		node = node->sig;
	}
	printf("\n");
}


