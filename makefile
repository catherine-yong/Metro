CC = gcc
CCFLAGS = -Wall 
COMPILE = $(CC) $(CCFLAGS)  -o $@

% ajouter définitions de PROGRAMS

all: $(PROGRAMS)

Main : main.c truc.c liste.c lire_station.c abr.c lire_ligne.c dijkstra.c truc.h coord.h liste.h station.h aqrtopo.h (? à revoir le nom) 
	$(COMPILE) main.c

Truc : truc.c truc.h coord.h
	$(COMPILE) truc.c

Liste : liste.c liste.h station.h truc.h
	$(COMPILE) liste.c

Lire_Station : lire_station.c liste.h
	$(COMPILE) lire_station.c

ABR : abr.c arbr_type.h aqrtopo.h liste.h truc.h station.h
	$(COMPILE) abr.c

Lire_Ligne : lire_ligne.c ligne.h
	$(COMPILE) liste_ligne.c

AQR : aqr.c abr.h aqr.h liste.h 
	$(COMPILE) aqr.c

Dijkstra : dijkstra.c truc.h liste.h 
	$(COMPILE) dijkstra.c

clean:
	rm -f $(PROGRAMS)
