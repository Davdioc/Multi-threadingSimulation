#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

void initGhost(GhostType** ghost){
	*ghost = malloc(sizeof(HunterType));
	int picker = randInt(0, 4);
	if(picker == 0){
		(*ghost)->ghostType = POLTERGEIST;
	}else if(picker == 1){
		(*ghost)->ghostType = BANSHEE;
	}else if(picker == 2){
		(*ghost)->ghostType = BULLIES;
	}else{
		(*ghost)->ghostType = PHANTOM;
	}
	(*ghost)->timer = BOREDOM_MAX;
	(*ghost)->currRoom = malloc(sizeof(RoomType));
	initRoom(&(*ghost)->currRoom, "");
}
void dropEvidence(GhostType* ghost){
	int ghostlyEvidence = randInt(0, 3);
	EvidenceType* evi = NULL;
	if(ghost->ghostType == POLTERGEIST){//Generate and store evidence for the a POLTERGEIST
		if(ghostlyEvidence == 0){
			initEvidence(randFloat(4.70, 5.00), EMF, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped EMF evidence in the %s\n", ghost->currRoom->name);
		}else if(ghostlyEvidence == 1){
			initEvidence(randFloat(-10, 1.00), TEMPERATURE, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped TEMPERATURE evidence in the %s\n", ghost->currRoom->name);
		}else{
			initEvidence(1, FINGERPRINTS, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped FINGERPRINTS evidence in the %s\n", ghost->currRoom->name);
		}  
	}else if(ghost->ghostType == BANSHEE){//Generate and store evidence for the a BANSHEE
		if(ghostlyEvidence == 0){
			initEvidence(randFloat(4.70, 5.00), EMF, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped EMF evidence in the %s\n", ghost->currRoom->name);
		}else if(ghostlyEvidence == 1){
			initEvidence(randFloat(-10, 1.00), TEMPERATURE, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped TEMPERATURE evidence in the %s\n", ghost->currRoom->name);
		}else{
			initEvidence(randFloat(65.00, 75.00), SOUND, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped SOUND evidence in the %s\n", ghost->currRoom->name);
		}  
	}else if(ghost->ghostType == BULLIES){//Generate and store evidence for the a BULLIES
		if(ghostlyEvidence == 0){
			initEvidence(randFloat(4.70, 5.00), EMF, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped EMF evidence in the %s\n", ghost->currRoom->name);
		}else if(ghostlyEvidence == 1){
			initEvidence(randFloat(65.00, 75.00), SOUND, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped SOUND evidence in the %s\n", ghost->currRoom->name);
		}else{
			initEvidence(1, FINGERPRINTS, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped FINGERPRINTS evidence in the %s\n", ghost->currRoom->name);
		}
	}else{
		if(ghostlyEvidence == 0){//Generate and store evidence for the a PHANTOM
			initEvidence(randFloat(-10, 1.00), TEMPERATURE, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped TEMPERATURE evidence in the %s\n", ghost->currRoom->name);
		}else if(ghostlyEvidence == 1){
			initEvidence(randFloat(65.00, 75.00), SOUND, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped SOUND evidence in the %s\n", ghost->currRoom->name);
		}else{
			initEvidence(1, FINGERPRINTS, evi);
			appendEvidence(ghost->currRoom->evidences,evi);
			printf("Ghost dropped FINGERPRINTS evidence in the %s\n", ghost->currRoom->name);
		}
	}
}

void adjustGhost(GhostType* ghost){
	int hunter = C_FALSE;
	if(ghost->currRoom->hunterNum != 0){//Check if there is any hunter in the room with the ghost
		hunter = C_TRUE;	
		
	}
	if(hunter == C_TRUE){//when hunter is present
		ghost->timer =  BOREDOM_MAX;
		int evidence_decision = randInt(0, 2);
		if(evidence_decision == 1){
			dropEvidence(ghost);
		}	
	}else{
		ghost->timer--;
		int evidence_decision = randInt(0, 2);
		if(evidence_decision == 1){
			dropEvidence(ghost);
		}
	}	
	
}

void placeGhost(RoomListType* rooms, GhostType* ghost){
	RoomNodeType* current = rooms->head;
	int rand = randInt(1,(rooms->size));
	int counter = 0;
	while(counter != rand ){
		current= current->next;
		counter++;
	}
	current->room->ghost = ghost;
	ghost->currRoom = current->room;
	
	printf("Ghost spawned in the %s\n",ghost->currRoom->name);
	
}

void moveGhost(GhostType* ghost){
	int num;
	if(ghost->currRoom->connectSize ==1){
		num = 0;
	}else{
		num = randInt(0,(ghost->currRoom->connectSize));
	}
	RoomNodeType* curr = ghost->currRoom->connect->head;
	for(int i = 0; i<num; ++i)
		curr = curr->next;
	
	curr->room->ghost = ghost;
	ghost->currRoom = curr->room;
	ghost->currRoom->ghost = NULL;
	
	printf("Ghost moved to the %s\n",ghost->currRoom->name);
	
}
