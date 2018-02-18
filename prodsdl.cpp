#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "prodcom.h"
#include "CAKGraphics.h"


int main(int argc, char* args[]) 
{

	 CAKGraphics akgraphics;
	 pthread_t uid_in, uid_out;
	 cp_t nfccontext;

	 if( akgraphics.graphics_init() == true )
	 {
			 if( web_init() == true ){

				if( nfc_init(&nfccontext) == true )
				{

					initialise(&nfccontext, 5);
					pthread_create(&uid_in, NULL, nfc_in_handler, (void *) &nfccontext);
					pthread_create(&uid_out, NULL, web_out_handler, (void *) &nfccontext);

			
					akgraphics.graphics_background("./images/typhoon.bmp"); 
					akgraphics.graphics_text("Tap to Sign In", {0,0,0x3F} );

					akgraphics.graphics_updatewindow();
					
					akgraphics.graphics_run(&nfccontext);
			
					pthread_join(uid_in, NULL);
					pthread_join(uid_out, NULL);
					
					akgraphics.graphics_destroy();
					nfc_exit(&nfccontext);
				}
		  }
	 }
	  return 0;
}
