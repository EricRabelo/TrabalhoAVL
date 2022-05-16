all: teste

teste: hospede.o ArvBinAvl.o
	gcc -o teste hospede.o ArvBinAvl.o

hospede.o: hospede.c ArvBinAvl.h
	gcc -c -o hospede.o hospede.c -Wall

ArvBinAvl.o: ArvBinAvl.c
	gcc -c -o ArvBinAvl.o ArvBinAvl.c -Wall

clean:
	rm hospede.o ArvBinAvl.o teste
