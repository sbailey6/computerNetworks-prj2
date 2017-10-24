.c.o:
	gcc -g -c $?

all: 
	gcc -g -o netTopology virtualNetwork.c


clean:
	rm -f *.o netTopology
