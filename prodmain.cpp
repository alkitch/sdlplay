#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "prodcom.h"


int main(int argc, char *argv[])
 {

    cp_t nfccontext;

	if( web_init() == true ){

		if( nfc_init(&nfccontext) == true )
		{

			initialise(&nfccontext, 5);
		
			pthread_t uid_in, uid_out;
			
#ifdef Monitor	    
			pthread_t m;
#endif	    
			
			pthread_create(&uid_in, NULL, nfc_in_handler, (void *) &nfccontext);
			pthread_create(&uid_out, NULL, web_out_handler, (void *) &nfccontext);

#ifdef Monitor	  	    
			pthread_create(&m, NULL, monitor, (void *) &nfccontext);
#endif

			pthread_join(uid_in, NULL);
			pthread_join(uid_out, NULL);
			
#ifdef Monitor	    
			pthread_join(m, NULL);
#endif        

		}
		nfc_exit(&nfccontext);
	}
    exit(0);


} 
