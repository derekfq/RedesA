all: client

client: json.o client.o
	gcc -o client json.o client.o

json.o: json.c
	gcc -c json.c

client.o: client.c
	gcc -c client.c


# Exclui os objetos
clean:
	rm -rf *.o

# Exclui o executável
rmproper: clean
	rm -rf client_server