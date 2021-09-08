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
#include <string.h>

void creatPhilosophers( int nthreads );
void* philosopherThread( void* pVoid );

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

   //free malloced memory to avoid memory leaks
   free(pVoid);

   return NULL;

}

