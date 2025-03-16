#include "defs.h"
#include <stdlib.h>

void initHunter(char* name, EvidenceClassType reader, HunterType** hunter, RoomListType** roomList){
	*hunter = malloc(sizeof(HunterType));
	strcpy((*hunter)->name,name);
	(*hunter)->fear = 0;
	(*hunter)->timer = BOREDOM_MAX;
	(*hunter)->reader = reader;
	(*hunter)->currRoom = (*roomList)->head;
	
}

void setHunters(HunterType** hunter1,HunterType** hunter2, HunterType** hunter3, HunterType** hunter4, RoomListType** roomList){
//user gives name of hunters according to their devices
	char h1[MAX_STR];//h1's name
	char h2[MAX_STR];//h2's name
	char h3[MAX_STR];//h3's name
	char h4[MAX_STR];//h4's name
	printf("Input the name of the first hunter, with the EMF device\n");
	fgets(h1,sizeof(h1),stdin);
	
	printf("Input the name of the second hunter, with the Temperature device\n");
	fgets(h2,sizeof(h2),stdin);
	
	printf("Input the name of the third hunter, with the Fingerprints device\n");
	fgets(h3,sizeof(h3),stdin);
	
	printf("Input the name of the fourth hunter, with the Sound device\n");
	fgets(h4,sizeof(h4),stdin);
	initHunter(h1, EMF, hunter1, roomList);
	initHunter(h2,TEMPERATURE, hunter2, roomList);
	initHunter(h3, FINGERPRINTS, hunter3, roomList);
	initHunter(h4, SOUND, hunter4, roomList);
}
