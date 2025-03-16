#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR            64
#define FEAR_RATE           1
#define MAX_FEAR          100
#define MAX_HUNTERS         4
#define USLEEP_TIME     50000
#define BOREDOM_MAX        99

#define C_TRUE     1
#define C_FALSE    0

// You may rename these types if you wish
typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceClassType;

typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;

typedef struct{
	EvidenceClassType evidenceType;
	float data;
	
} EvidenceType;

typedef struct evNode{
	EvidenceType* dat;
	struct evNode* next;
} EvidenceNodeType;

typedef struct{
	EvidenceNodeType* head;
} EvidenceListType;

typedef struct{
	EvidenceClassType reader;
	struct Room* currRoom;
	EvidenceListType* evidences;
	char name[MAX_STR];
	int fear;
	int timer;
	sem_t mutex;
	
} HunterType;

typedef struct Room{
	char name[MAX_STR];
	HunterType *hunter[MAX_HUNTERS];
	int hunterNum;
	struct Ghost* ghost;
	EvidenceListType* evidences;
	struct RoomList* connect;
	int  connectSize;
} RoomType;

typedef struct Ghost{
	GhostClassType ghostType;
	RoomType* currRoom;
	int timer;
} GhostType;

typedef struct Node{
	RoomType* room;
	struct Node* next;
} RoomNodeType;

typedef struct RoomList{
	RoomNodeType* head;
	int size;
} RoomListType;

typedef struct{
	RoomListType rooms;
} BuildingType;

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

void initHunter(char* name, EvidenceClassType reader, HunterType** hunter);
void initRoom(RoomType** room, char* name);
void initGhost(GhostType** ghost);
void initEvidence(float data, EvidenceClassType type, EvidenceType* evi);
void initEvidenceList(EvidenceListType* eviList);
void initRoomList(RoomListType *rooms);
void initBuilding(BuildingType* building);

void cleanupList(EvidenceListType* eviList);

void populateRooms(BuildingType*);   // Populates the building with sample data for rooms

void dropEvidence(GhostType* ghost);
void adjustGhost(GhostType* ghost);
void adjustHunter(HunterType* hunter);
void appendEvidence(EvidenceListType* eviList, EvidenceType* evi);
void appendRoom(RoomListType* rooms, RoomNodeType* node);
void connectRooms(RoomType* room1, RoomType* room2);
void placeGhost(RoomListType* rooms, GhostType* ghost);
void placeHunter(RoomType* room, HunterType* hunter);
void pickEvidence(HunterType* hunter);
void deleteEvidence(EvidenceListType *eviList, EvidenceClassType evidenceType, float data);
void moveGhost(GhostType* ghost);
