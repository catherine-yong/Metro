#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "liste.h"

int main()
{
   char *station;
   station = lire_stations("../stations_metro.csv"); 
}