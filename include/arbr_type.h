#ifndef ABR 
#define ABR 1
#include "truc.h"

typedef struct _un_nabr { 
    Un_truc *truc; /*La station*/
    struct _un_nabr *g; /*Fils gauche strictement inferieur*/ 
    struct _un_nabr *d; /*Fils droit*/
} Un_nabr; 

#endif