CC = gcc
CCFLAGS = -Wall 
COMPILE = $(CC) $(CCFLAGS)  -o $@

all: $(PROGRAMS)

Truc : truc.c truc.h coord.h
	$(COMPILE) truc.c

Liste : liste.c liste.h station.h truc.h
	$(COMPILE) liste.c

Lire_Station : lire_station.c liste.h my.h
	$(COMPILE) lire_station.c

ABR : abr.c arbr_type.h aqrtopo.h liste.h truc.h station.h
	$(COMPILE) abr.c

Liste_Ligne : liste_ligne.c ligne.h
	$(COMPILE) liste_ligne.c

Connexions : connexions.c liste.h lignes.h abr.h
	$(COMPILE) connexions.c

AQR : aqr.c abr.h aqr.h liste.h 
	$(COMPILE) aqr.c

Dijkstra : dijkstra.c truc.h liste.h 
	$(COMPILE) dijkstra.c

clean:
	rm -f $(PROGRAMS)
