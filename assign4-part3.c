/**************************************************
*Hunter Long
*mia014
*CS-3733-01T
*Assignment 4
*August 9th, 2021
**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void creatPhilosophers( int nthreads );
void* philosopherThread( void* pVoid );
void thinking(int threadIndex);
void pickUpChopsticks(int threadIndex); 
void eating(int threadIndex);
void putDownChopsticks(int threadIndex);

int nextIndex = 0;
pthread_mutex_t lock;
pthread_cond_t myTurn;

int main( int argc, char* argv[] ){

   //usage statement
   if( argc != 2 ){
      printf( "Usage: %s <number of threads>\n", argv[0] );
      return -1;
   }

   //process command line arguement to retreive the value of nthreads
   int nthreads;
   if( (nthreads = atoi( argv[1] ) ) == 0 ){
      printf( "Invalid option - must enter integer greater than 0 number of threads to create.\n" );
      return -1;
   }

   //print "by line" and value of nthreads
   printf( "Hunter Long - Assignment 4: # of threads = %d\n", nthreads );

   //initialize mutext lock and conditon variable to standard start 
   pthread_mutex_init( &lock, NULL );
   pthread_cond_init( &myTurn, NULL );

   //invoke creatPhilosophers()
   creatPhilosophers( nthreads );

   return 0;

}

void creatPhilosophers( int nthreads ){

   //array of thread identifiers for threads that will be created 
   pthread_t threads[nthreads];

   //loop nthreads number of times, create threads, and pass them their index
   int i;
   for( i = 0; i < nthreads; i++ ){
      int* value = (int*)malloc(sizeof(int));
      *value = i;
      pthread_create( &threads[i], NULL, philosopherThread, ( (void*) value ) );
   }

   //join all threads created to ensure they finish executing before the main thread terminates
   for( i = 0; i < nthreads; i++ ){
      pthread_join( threads[i], NULL );
   }

   //print success statement
   printf( "%d threads have been created/joined successfully!\n", nthreads );

   return;

}

void* philosopherThread( void* pVoid ){

   //process thread index from void* back to int
   int philNum = *( (int*) pVoid );

   //print output 
   printf( "This is philosopher %d\n", philNum );

   //call thinking (every philosopher can think at the same time)
   thinking( philNum );

   //grab lock so we can wait on conditional variable (doesn't matter the order they grab the lock in 
   //because if its not their turn to eat they'll sleep 
   pthread_mutex_lock(&lock);

   //sleep until it is this threads turn to eat 
   while(philNum != nextIndex){
      pthread_cond_wait(&myTurn, &lock);
   }

   //call eating
   eating( philNum );

   //release lock so next philosopher can eat 
   pthread_mutex_unlock(&lock);

   //iterate nextIndex before waking up other threads so there's no confusion 
   nextIndex++;

   //wake up all other threads to find out which ones turn it is now 
   pthread_cond_broadcast( &myTurn );

   //free malloced memory to avoid memory leaks
   free(pVoid);

   return NULL;

}

void thinking( int threadIndex ){

   //generate random "thinking" time
   unsigned int waitTime = (random() % (500 - 1 + 1)) + 1;
   //print start thinking message
   printf( "Philosopher #%d: starts thinking\n", threadIndex );
   //spend time "thinking"
   usleep( waitTime );
   //print end thinking message 
   printf( "Philosopher #%d: ends thinking\n", threadIndex );

   return;

}

void pickUpChopsticks(int threadIndex){
   
   //lock the mutex (pick up chopsticks)
   pthread_mutex_lock( &lock );

   //return to eat 
   return; 

}

void eating( int threadIndex ){

   //generate random "eating" time
   unsigned int waitTime = (random() % (500 - 1 + 1)) + 1;
   //print start eating message
   printf( "Philosopher #%d: starts eating\n", threadIndex );
   //spend time "eating"
   usleep( waitTime );
   //print end eating message
   printf( "Philosopher #%d: ends eating\n", threadIndex );

   return;

}

void putDownChopsticks(int threadIndex){

   //unlock mutex (put down chopsticks) so next philosopher can eat 
   pthread_mutex_unlock( &lock );

   //return to terminate
   return; 

}

