#include <nfc/nfc.h>
#include <nfc/nfc-types.h>


#define ONE_SECOND 1000000
#define RANGE 10
#define PERIOD 2
#define NUM_THREADS 2 

typedef struct {
  int *nfcuid;
  int capacity;
  int occupied;
  int nextin;
  int nextout;
  int uids_in;
  int uids_out;
  pthread_mutex_t lock;
  pthread_cond_t space;
  pthread_cond_t uid;
  pthread_barrier_t bar;
  
  nfc_device *pnd;
  nfc_context *context;
  volatile bool quitflag;
} cp_t;


bool nfc_init(void *nfc_context);
void nfc_exit(void *nfc_context);
void *nfc_in_handler(void *nfc_context);

bool web_init(void);
void *web_out_handler(void *nfc_context);

#ifdef Monitor
void *monitor(void *cp_in);
#endif

void initialise(cp_t *cp, int size);
