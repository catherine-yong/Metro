
main : main.o abr.o aqrtopo.o liste.o station.o truc.o
	gcc main.o abr.o aqrtopo.o liste.o station.o truc.o -o main
	make clean
48.89200565400341, 2.236983123817432

main.o : main.c *.h
	gcc -c main.c
	
abr.o : abr.c *h
	gcc -c abr.c
	
aqrtopo.o : aqrtopo.c *.h
	gcc -c aqrtopo.c 
	
liste.o : liste.c *.h
	gcc -c liste.c 
	
station.o : station.c *.h
	gcc -c station.c
	
truc.o : truc.c *.h
	gcc -c truc.c
