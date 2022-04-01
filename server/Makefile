all: server

server: json.o server.o
	gcc -o server json.o server.o

json.o: json.c
	gcc -c json.c

server.o: server.c
	gcc -c server.c
	

# Exclui os objetos
clean:
	rm -rf *.o

# Exclui o executável
rmproper: clean
	rm -rf server