#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(){
	key_t key;
	int shmid;
	char * data;
	char userinput[256];

	key = ftok("./key_file", 'R');
	shmid = shmget(key, 201 * sizeof(char *), 0666 | IPC_CREAT);
	data = shmat(shmid, (void *)0 , 0);

	if(data[0]){ // if data exists
		printf("Data already exists: %s\n", data);
	} else {
		printf("Data just created!\n");
	}

	printf("\nDo you want to change this data [y/n]: ");
	fgets(userinput, 200, stdin);
	printf("\n");
	if(userinput[0] == 'y'){
			printf("What do you want to write?\n");
			fgets(userinput, 200, stdin);
			// null terminate
			userinput[strlen(userinput) - 1] = 0;
			strcpy(data, userinput);
	}

	printf("Delete the data [y/n]? ");
	fgets(userinput, 200, stdin);
	printf("\n");

	if(userinput[0] == 'y'){
		shmdt(data);
		shmctl(shmid, IPC_RMID, NULL);
	}



	return 0;
}
