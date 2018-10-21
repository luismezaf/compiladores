/*********** Librerias utilizadas **************/
#include "tokensQueue.h"

/*********** Prototipos **************/
void initansin(listatokens *listt);
void match(int expToken);
void sintError(char* expTok);
char *numToLexema(int num);
void p_json();
void p_element();
void p_object();
void p_attr_list();
void p_ap();
void p_element_list();
void p_ep();
void p_op();
void p_alp();
void p_attribute();
void p_att_name();
void p_att_value();
