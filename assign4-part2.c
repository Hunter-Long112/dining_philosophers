/**************************************************
*Hunter Long
*CS-3733
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

int numThreads;
pthread_mutex_t* chopstix;

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

   //set global numThreads to the number of threads so the "0th" philosopher can find his left chopstick
   numThreads = nthreads;

   //print "by line" and value of nthreads
   printf( "Hunter Long - Assignment 4: # of threads = %d\n", nthreads );

   //create the array of mutex locks to represent the chopsticks and initialize them to unlocked 
   pthread_mutex_t* chopsticks = (pthread_mutex_t*)malloc( sizeof(pthread_mutex_t) * nthreads);
   int i;
   for( i = 0; i < nthreads; i++ ){
      pthread_mutex_init( &chopsticks[i], NULL );
   }

   //set global pointer chopstix to the array of mutexes that represent chopsticks so the threads can interact with them 
   chopstix = chopsticks;

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

   //join all threads created to ensure they finish executing before the main thread terminatees
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

   //call each function in cycle for philosophers in order, passing their thread index 
   thinking( philNum );
   pickUpChopsticks( philNum );
   eating( philNum );
   putDownChopsticks( philNum );

   //free malloced memory to avoid memory leaks
   free(pVoid);

   return NULL;

}

void thinking( int threadIndex ){

   //generate random think time 
   unsigned int waitTime = (random() % (500 - 1 + 1)) + 1;
   //print start thinking message
   printf( "Philosopher #%d: starts thinking\n", threadIndex );
   //spend time "thinking"
   usleep( waitTime );
   //print done thinking message 
   printf( "Philosopher #%d: ends thinking\n", threadIndex );

   return;

}

void pickUpChopsticks(int threadIndex){
   
   int left, right;

   //find left and right "chopstick" index for specific philosopher
   if( threadIndex == 0 ){
      left = numThreads - 1;
   }
   else{
      left = threadIndex - 1;
   }
   right = threadIndex;

   //debugging output
   //printf( "Philosopher #%d picking up left chopstick (index = %d)\n", threadIndex, left );

   //lock left "chopstick" (if not availible lock will automatically wait until it is) 
   pthread_mutex_lock( &chopstix[left] );

   //dubugging output
   //printf( "Philosopher #%d picking up right chopstick (index = %d)\n", threadIndex, right );

   //lock right "chopstick" (if not availible lock will automatically wait until it is) 
   pthread_mutex_lock( &chopstix[right] );

   //once both are locked return to eat 
   return; 

}

void eating( int threadIndex ){

   //generate random "eat" time
   unsigned int waitTime = (random() % (500 - 1 + 1)) + 1;
   //print start eating message 
   printf( "Philosopher #%d: starts eating\n", threadIndex );
   //spend time "eating"
   usleep( waitTime );
   //print done eating message
   printf( "Philosopher #%d: ends eating\n", threadIndex );

   return;

}

void putDownChopsticks(int threadIndex){

   int left, right;

   //find left and right "chopstick" index for specific philosopher
   if( threadIndex == 0 ){
      left = numThreads - 1;
   }
   else{
      left = threadIndex - 1;
   }
   right = threadIndex;

   //debugging output
   //printf( "Philosopher #%d put down left chopstick (index = %d)\n", threadIndex, left );

   //unlock left "chopstick" 
   pthread_mutex_unlock( &chopstix[left] );

   //debugging output
   //printf( "Philosopher #%d put down right chopstick (index = %d)\n", threadIndex, right );

   //unlock right "chopstick"
   pthread_mutex_unlock( &chopstix[right] );

   return; 

}


