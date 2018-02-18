#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>


#include "prodcom.h"

int ResolveUidFromNfcTarget(nfc_target* pnt);

  const uint8_t uiPollNr =30;
  const uint8_t uiPeriod = 1;
  const nfc_modulation nmModulations[5] = {
    { .nmt = NMT_ISO14443A, .nbr = NBR_106 },
    { .nmt = NMT_ISO14443B, .nbr = NBR_106 },
    { .nmt = NMT_FELICA, .nbr = NBR_212 },
    { .nmt = NMT_FELICA, .nbr = NBR_424 },
    { .nmt = NMT_JEWEL, .nbr = NBR_106 },
  };
  const size_t szModulations = 5;  //Making this 2 polls for just ISO14443A and B which is much quicker


void initLEDS()
{
	  wiringPiSetup();
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
}

void toggleLEDS(bool on)
{
	if( on == true )
	{
		digitalWrite(0, HIGH);
		digitalWrite(1, LOW);
	}
	else {
		        digitalWrite(0,LOW);
		digitalWrite(1, HIGH);
	}
}

void offLEDS()
{
		digitalWrite(0, LOW);
		digitalWrite(1, LOW);
}


bool nfc_init(void *nfc_context)
{
	cp_t *temp = (cp_t *)nfc_context;
	
#ifdef _DEBUG	
  	printf("Using libnfc %s\n", nfc_version() );
#endif
  	
  	nfc_init(&temp->context);
  	if( temp->context == NULL )
			return false;
			
	temp->pnd = nfc_open(temp->context, NULL);
	if( temp->pnd == NULL ){
			nfc_exit(temp->context);
			return false;
		}
			
			
	if (nfc_initiator_init(temp->pnd) < 0) {
		nfc_close(temp->pnd);
		nfc_exit(temp->context);
		return false;
  }

#ifdef _DEBUG
  printf("NFC reader: %s opened\n", nfc_device_get_name(temp->pnd));
#endif		

   initLEDS();

  return true;
}

void nfc_exit(void *nfc_context)
{
	cp_t *temp = (cp_t *)nfc_context;
	nfc_close(temp->pnd);
	nfc_exit(temp->context);
}

void* nfc_in_handler(void *nfc_context)
{

	nfc_target nt;
    //unsigned int seed;
    cp_t *temp = (cp_t *)nfc_context;
    
    

    pthread_barrier_wait(&temp->bar);
    while(temp->quitflag == false) { 

        //usleep(rand_r(&seed) % ONE_SECOND);
        int res = nfc_initiator_poll_target(temp->pnd, nmModulations, szModulations, uiPollNr, uiPeriod, &nt);

        if( res > 0 )
        {
			
			toggleLEDS(true);
			//try to find the uidvalue from nt;
			int uidvalue = ResolveUidFromNfcTarget(&nt);
			pthread_mutex_lock(&temp->lock);

			//while full wait until there is room available
			while (temp->occupied == temp->capacity)
				pthread_cond_wait(&temp->space, &temp->lock);

			//insert an item
			temp->nfcuid[temp->nextin] = uidvalue ;

			//increment counters

			temp->occupied++;
			temp->nextin++;
			temp->nextin %= temp->capacity; //circular buffer here then
			temp->uids_in++;

			//someone may be waiting on data to become available
			pthread_cond_signal(&temp->uid);

			//release the lock
			pthread_mutex_unlock(&temp->lock);
                
        while (0 == nfc_initiator_target_is_present(temp->pnd, NULL)) {}
        
		toggleLEDS(false);
        }

    }
    offLEDS();
    nfc_exit(nfc_context);
    return ((void *)NULL);

}

int ResolveUidFromISO14443A( nfc_iso14443a_info* pnai )
{
	int i = (int)(pnai->szUidLen - 4);
	int n = 0;
	
	n |= pnai->abtUid[i];
	n <<= 8;
	n |= pnai->abtUid[i+1];
	n <<= 8;	
	n |= pnai->abtUid[i+2];
	n <<= 8;
	n |= pnai->abtUid[i+3];
	
	return n;
	
}

int ResolveUidFromNfcTarget(nfc_target* pnt)
{
		
	switch( pnt->nm.nmt )
	{
	case NMT_ISO14443A:
        return ResolveUidFromISO14443A( &pnt->nti.nai );
        break;
        /*
      case NMT_JEWEL:
        return ResolveUidFromJewel(&pnt->nti.nji);
        break;
      case NMT_BARCODE:
        return ResolveUidFromBarcode(&pnt->nti.nti);
        break;
      case NMT_FELICA:
        return ResolveUidFromFelica(&pnt->nti.nfi);
        break;
      case NMT_ISO14443B:
        return ResolveUidFromIso14443b(&pnt->nti.nbi);
        break;
      case NMT_ISO14443BI:
        return ResolveUidFromIso14443bi(&pnt->nti.nii);
        break;
      case NMT_ISO14443B2SR:
        return ResolveUidFromIso14443b2sr(&pnt->nti.nsi);
        break;
      case NMT_ISO14443B2CT:
        return ResolveUidFromIso14443b2ct(&pnt->nti.nci);
        break;
      case NMT_DEP:
        return  ResolveUidFromDep_info(&pnt->nti.ndi);
        break;
        */
	  default:
			return 0xFFAABBCC;
	}
	
}


