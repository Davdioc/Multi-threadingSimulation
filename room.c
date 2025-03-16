#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

void initRoom(RoomType** room, char* name){
	*room = malloc(sizeof(RoomType));
	strcpy((*room)->name,name);
	(*room)->ghost = NULL;
	(*room)->connectSize = 0;
	//(*room)->hunter = malloc(sizeof(HunterType));
	(*room)->hunterNum = 0;
	(*room)->connect = malloc(sizeof(RoomListType));
	initRoomList((*room)->connect);
	(*room)->evidences = malloc(sizeof(EvidenceListType));
	initEvidenceList((*room)->evidences);
}

void initRoomList(RoomListType *rooms){
	rooms->head = NULL ;
	rooms->size = 0; 
}

void appendRoom(RoomListType* rooms, RoomNodeType* node){  
	if(rooms->head == NULL){
		//rooms->head = malloc(sizeof(RoomNodeType));
		rooms->head= node;
		rooms->head->next = NULL;
		rooms->size++;
		return;
	}
	RoomNodeType* current;
	current=rooms->head;
	current->next = rooms->head->next;
	while(current->next != NULL){
		current= current->next;
	}
	current->next = node;
	node->next = NULL;
	rooms->size++;
}

void connectRooms(RoomType* room1, RoomType* room2){
	RoomNodeType* roomN1 = malloc(sizeof(RoomNodeType)); 
	RoomNodeType* roomN2 = malloc(sizeof(RoomNodeType));
	roomN1->room = room1;
	roomN2->room = room2;
	 
	appendRoom(room1->connect, roomN2);
	appendRoom(room2->connect, roomN1);
	room1->connectSize++;
	room2->connectSize++;
}
