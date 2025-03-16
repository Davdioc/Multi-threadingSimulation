#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

void initEvidence(float data, EvidenceClassType type, EvidenceType* evi){
	evi = malloc(sizeof(EvidenceType));
	evi->evidenceType = type;
	evi->data = data;
}
void initEvidenceList(EvidenceListType* eviList){
	eviList->head = NULL ;
}

void appendEvidence(EvidenceListType* eviList, EvidenceType* evi){
	EvidenceNodeType* new = NULL;
	new = malloc(sizeof(EvidenceNodeType));
	new->dat = evi;
	new->next = NULL; 
	if(eviList->head == NULL){
		eviList->head= new;
		eviList->head->next = NULL;
		return;
	}
	EvidenceNodeType* current;
	current= eviList->head;
	current->next = eviList->head->next;
	while(current->next != NULL){
		current= current->next;
	}
	current->next = new;
	new->next = NULL;
}
void deleteEvidence(EvidenceListType *eviList, EvidenceClassType evidenceType, float data) {
  EvidenceNodeType* curr = NULL;
  EvidenceNodeType* prev = NULL;
  curr = eviList->head;
  if(eviList->head->dat->evidenceType == evidenceType && eviList->head->dat->data == data ){
    free(eviList->head->dat);
    curr = eviList->head; 
    eviList->head = eviList->head->next;
    free(curr);
    return;
  }
  while(curr != NULL && eviList->head->dat->evidenceType != evidenceType && eviList->head->dat->data != data){
    prev = curr;
    curr=curr->next;
  }
  prev->next = curr->next;
  free(curr->dat);
  free(curr);
}

void cleanupList(EvidenceListType* eviList) {
  EvidenceNodeType* curr = NULL;
  EvidenceNodeType* prev = NULL;
  curr = eviList->head;
  while(curr != NULL ){
    prev = curr;
    curr=curr->next;
    free(prev->next);
    free(prev->dat);
  }
  free(curr);
  free(eviList);
}
