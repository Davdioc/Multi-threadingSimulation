#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "defs.h"

void *ghostwork(void *gh);
void *hunterwork(void *ht);

int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));

    // Initialize building
    BuildingType building;
    initBuilding(&building);
    populateRooms(&building);

    // Initialize hunter
    HunterType *hunter[MAX_HUNTERS];
    char h1[MAX_STR]; // h1's name
    char h2[MAX_STR]; // h2's name
    char h3[MAX_STR]; // h3's name
    char h4[MAX_STR]; // h4's name
    printf("Input the name of the first hunter, with the EMF device\n");
    fgets(h1, MAX_STR, stdin);

    printf("Input the name of the second hunter, with the Temperature device\n");
    fgets(h2, MAX_STR, stdin);

    printf("Input the name of the third hunter, with the Fingerprints device\n");
    fgets(h3, MAX_STR, stdin);

    printf("Input the name of the fourth hunter, with the Sound device\n");
    fgets(h4, MAX_STR, stdin);

    for (int i = 0; i < MAX_STR; ++i)
    {
        if (h1[i] == '\n')
        {
            h1[i] = '\0';
            break;
        }
        if (h2[i] == '\n')
        {
            h2[i] = '\0';
            break;
        }
        if (h3[i] == '\n')
        {
            h3[i] = '\0';
            break;
        }
        if (h4[i] == '\n')
        {
            h4[i] = '\0';
            break;
        }
    }
    initHunter(h1, EMF, &hunter[0]);
    initHunter(h2, TEMPERATURE, &hunter[1]);
    initHunter(h3, FINGERPRINTS, &hunter[2]);
    initHunter(h4, SOUND, &hunter[3]);
    for (int i = 0; i < MAX_HUNTERS; ++i)
        placeHunter(building.rooms.head->room, hunter[i]);

    // Initialize Ghost
    GhostType *ghost;
    initGhost(&ghost);
    placeGhost(&building.rooms, ghost);

    // Initialize semaphore
    sem_init(&((*hunter)->mutex), 0, 1);

    // Initialize threads
    pthread_t h_threads[MAX_HUNTERS];
    pthread_t g_thread;

    // Create thread
    for (int i = 0; i < MAX_HUNTERS + 1; ++i)
    {
        if (i == MAX_HUNTERS)
        {
            pthread_create(&g_thread, NULL, ghostwork, ghost);
        }
        else
        {
            pthread_create(h_threads + i, NULL, hunterwork, hunter[i]);
        }
    }

    // Join thread
    for (int i = 0; i < MAX_HUNTERS + 1; ++i)
    {
        if (i == MAX_HUNTERS)
        {
            pthread_join(g_thread, NULL);
        }
        else
        {
            pthread_join(h_threads[i], NULL);
        }
    }

    return 0;
}

/*
  Function:  randInt
  Purpose:   returns a pseudo randomly generated number,
             in the range min to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max-1)
*/
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}

/*
  Function:  randFloat
  Purpose:   returns a pseudo randomly generated number,
             in the range min to max, inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1)
*/
float randFloat(float a, float b)
{
    // Get a percentage between rand() and the maximum
    float random = ((float)rand()) / (float)RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}
void *hunterwork(void *ht)
{
    HunterType *hunter = (HunterType *)ht;
    // printf("%d", ghost->timer);
    while (hunter->timer > 0)
    {
        sem_wait(&((hunter)->mutex));
        moveHunter(hunter);
        sem_post(&((hunter)->mutex));
        sem_wait(&((hunter)->mutex));
        adjustHunter(hunter);
        sem_post(&((hunter)->mutex));
    }
    sem_wait(&((hunter)->mutex));
    printf("%s got bored and exited the building\n", hunter->name);
    sem_post(&((hunter)->mutex));
    return 0;
}

void *ghostwork(void *gh)
{
    GhostType *ghost = (GhostType *)gh;
    while (ghost->timer > 0)
    {
        moveGhost(ghost);
        adjustGhost(ghost);
    }
    printf("Ghost got bored and exited the building\n");
    return 0;
}
