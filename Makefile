CFLAGS = -Wall  # flags de compilacao
LDFLAGS = 

CC = g++

# arquivos-objeto
	objects = main.o avl-tree.o  

all: busca

busca: main.o avl-tree.o 
	$(CC) -o busca $(objects) $(LDFLAGS)

avl-tree.o: avl-tree.cpp avl-tree.hpp
	$(CC) -c $(CFLAGS) avl-tree.cpp

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

clean:
	rm -f $(objects) busca 
