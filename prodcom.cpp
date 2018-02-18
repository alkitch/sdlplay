#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include <CkJsonObject.h>
#include <CkHttpRequest.h>
#include <CkHttp.h>
#include <CkHttpResponse.h>
#include <CkXml.h>
#include "prodcom.h"



void initialise(cp_t *cp, int size) { 

    cp->occupied = cp->nextin = cp->nextout = cp->uids_in = cp->uids_out = 0;
    cp->capacity = size;
    cp->quitflag = false;

    cp->nfcuid = (int *)malloc(cp->capacity * sizeof(*cp->nfcuid));

    pthread_barrier_init(&cp->bar, NULL, NUM_THREADS);


    if(cp->nfcuid == NULL) {
        perror("malloc()");
        exit(1);
    }

    srand((unsigned int)getpid());

    pthread_mutex_init(&cp->lock, NULL);
    pthread_cond_init(&cp->space, NULL);
    pthread_cond_init(&cp->uid, NULL);
} 


#ifdef Monitor
void *monitor(void *nfc_context) {

    cp_t *temp;
    temp = (cp_t *)nfc_context;

    for(; ;) { 
    sleep(PERIOD);

    //acquire the lock
    pthread_mutex_lock(&temp->lock);
    printf("Delta: %d\n", temp->uids_in - temp->uids_out - temp->occupied);
    printf("Number of uids in nfcuid: %d\n", temp->occupied);

    //release the lock
pthread_mutex_unlock(&temp->lock);

    }

    return ((void *)NULL);
}
#endif



