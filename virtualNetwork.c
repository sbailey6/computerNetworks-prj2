#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 1

int initNet(char *netConfig){
	FILE *fd = fopen(netConfig, "r");
	if(fd == NULL){
		fprintf(stderr, "The given netConfig file, %s, doesn't exist.\n", netConfig);
		exit(1);
	}
	char line[256];
	//read each line from the netConfig file
	while(fgets(line, sizeof(line), fd)){
		//now we parse the line and create the node corrseponding to that line.
		printf(line);
		char * token;
		token = strtok(line, " ");
		while(token != NULL){
			printf("%s\n", token);
			token = strtok(NULL, " ");
		}

	}

	fclose(fd);
	return SUCCESS;
}

int main(int argc, char *argv[]){
	/*check for correct arguments*/
	if(argc != 2){
		fprintf(stderr, "usage: %s <netConfig file>\n", argv[0]);
		exit(1);
	}
	/*parse netConfig file and set up initial network topology*/
	int result = initNet(argv[1]);
	if(result < 0){
		fprintf(stderr, "The initialization of the network failed.");
		exit(1);
	}
}

/* 2: Distance Vector Routing 
	1. Each node will also have a distance vector initialized with some info about its 
	direct neighbors to start. The distance vector looks like this:
	<Destination, Next Hop, Distance> 
		Destination = where a packet is being sent
		Next Hop = where the pack should be first forwarded
		Distance = total number of hops required to reach destination
	2. each node will send its distance vector to its direct neighbors. This will info will be used 
	to update each Node's Routing Table. We should look at the slides and decide on a data structure to use for the Routing Table. 
	I think an array of structs could work for us, where the struct has all the info in a given row of the Routing Table. 
	Open to discussion on this though.
	3. To update the Routing Table, we will use the algorithm where we check and update entries 
	so that the shortest known distance is being stored.
	4. All of the exchange of routing messages, and distance vectors needs to be dne via
	 the node's Control Port, not the Data port. 
	5. Each node will have a dedicated control thread to handle the sending/receiving 
	of all routing messages through a select() call. 
	The threads will be made using pthreads.
	6. UPD sockets ate created using the socket() call, but we do not need to 
	listen or accept since they are connectionless. They will send and recieve information 
	from one another via the recvfrom() and sendto() functions, which the assignment description 
	briefly covers.
	7. We will need to deal with packets being too big (may require sending data in separate chunks),
	and also use the addr field to determine which sourve node has sent us a distance vector.  
*/

