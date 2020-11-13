#include <stdio.h>
#include <stdlib.h>
#include "ABR.h"
#include "ABQ.h"
#include "liste.h"


void detruire_aqr(Un_noeud* aqr)
{
    if(aqr == NULL)
        return;
    detruire_aqr(aqr -> no);
    detruire_aqr(aqr -> so);
    detruire_aqr(aqr -> ne);
    detruire_aqr(aqr -> se);
    free(aqr);
}
