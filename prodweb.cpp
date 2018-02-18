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
#include "CAKGraphics.h"


bool HttpPrepare(int v);

bool web_init(void)
{
   CkHttp httx;
   bool success = httx.UnlockComponent("Anything for 30-day trial");
    if (success != true) {
        printf("%s\r\n", httx.lastErrorText() );
        return false;
    }
	return true;
}



void* web_out_handler(void *nfc_context) {

    cp_t* temp = (cp_t *)nfc_context;
    pthread_barrier_wait(&temp->bar);
    while(temp->quitflag == false) { 

        //acquire the lock
        pthread_mutex_lock(&temp->lock);

    while(temp->occupied == 0) 
            pthread_cond_wait(&temp->uid, &temp->lock);


    HttpPrepare( temp->nfcuid[temp->nextout] );
    //increment counters
    temp->occupied--;
    temp->nextout++;
    temp->nextout %= temp->capacity;
    temp->uids_out++;


    //somebody may be waiting on toom to become available
    pthread_cond_signal(&temp->space);

    //release the locl
     pthread_mutex_unlock(&temp->lock);


    }
    return ((void *)NULL);

}

bool HttpPrepare(int v)
{
    CkHttp http;
    CkJsonObject json;

    bool success = json.AddIntAt(-1,"nRfid",v);
    if(success)
    {
     success = json.AddStringAt(-1,"RfidLocation","FrontDoor");
     json.put_EmitCompact(true);
    }

    http.put_AcceptCharset("");
    http.put_UserAgent("");
    http.put_AcceptLanguage("");
    http.put_AllowGzip(false);
    success = http.AddQuickHeader("Content-type","application/json");

#ifdef _DEBUG
    printf("%s\n", json.emit() );
#endif
    
    CkHttpResponse *resp = http.PostJson("http://alansw550/aweb2427/home/rfid",json.emit() ); 
    if (resp == 0 ) {
        printf("%s\r\n", http.lastErrorText() );
        return false;
    }
    else {
			
			char buf[2048];
			strcpy( buf, resp->bodyStr() );
			SDL_Event event;
			SDL_UserEvent userevent;

			userevent.type = SDL_USEREVENT;
			userevent.code = EVENT_TAP_FROM_WEBRESPONSE;
			char* p = (char*)malloc( strlen(buf)+1 );
			strcpy( p, buf);
			userevent.data1 = p;
			userevent.data2 = (void*)strlen(p);
			event.type = SDL_USEREVENT;
			event.user = userevent;

			SDL_PushEvent(&event);

			//  Display the JSON response.
			//printf("Response Body = %s\r\n", resp->bodyStr() );
        delete resp;
    }
    
    return true;
}
