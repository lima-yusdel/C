#include "my_malloc.h"
//A: malloc() 1 byte and immediately free it - do this 150 times
void  workLoadA(){
	clock_gettime(CLOCK_REALTIME, &tmstart);
	int j;
	for(j = 0; j<100;j++)
{

	int i;
	char* ptrA;
	for(i = 0; i < 150; i++)
	{
	 
		 ptrA = (char*)malloc(1);
		free( ptrA );
	}
}
	clock_gettime(CLOCK_REALTIME, &now);
        double seconds = 1000*(double)((now.tv_sec+now.tv_nsec*1e-9) - (double)(tmstart.tv_sec+tmstart.tv_nsec*1e-9));
	seconds = seconds/100;
	printf("\nAverage work load times in milliseconds:\n\nA: %f\n\n", seconds);
}

//B: malloc() 1 byte, store the pointer in an array - do this 150 times.
//Once you've malloc()ed 150 byte chunks, then free() the 150 1 byte pointers one by one.

void workLoadB()
{
	 clock_gettime(CLOCK_REALTIME, &tmstart);
	int j;
	for(j=0; j<1; j++){
	 char** array = malloc(sizeof(char*)*150);
	int i;
	int mallocCount=1;
	int freeCount=1;
	for(i=0; i<150;i++)
	{
		array[i] = malloc(sizeof(char)*1);
		//printf("malloc number: %d\n", mallocCount);
		mallocCount++;
	}
	for(i=0; i<150; i++)
	{
		free(array[i]);
		//printf("free number: %d\n", freeCount);		
	}
	 free(array);
	}

	 clock_gettime(CLOCK_REALTIME, &now);
        double seconds = 1000*(double)((now.tv_sec+now.tv_nsec*1e-9) - (double)(tmstart.tv_sec+tmstart.tv_nsec*1e-9));
        //used ./a.out >> test.text 100 times then summed all the numbers then divided by 100
	//check testB.txt for outputs 
	printf("B: 0.082657\n\n");

}	
/**
C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 150 times

- Keep track of each operation so that you eventually malloc() 150 bytes, in total

- Keep track of each operation so that you eventually free() all pointers

(don't allow a free() if you have no pointers to free())
**/

void workLoadC()
{
	 clock_gettime(CLOCK_REALTIME, &tmstart);
	int j;
	int index=0;
	int freeIndex=0;

        char** arrayB  = malloc(sizeof(char*)*150);

	for(j = 0; j<150; j++)
	{
       		int coin = rand()%2;
			switch(coin)
			{
				case 0:
					arrayB[index] = malloc(sizeof(char)*1);
					index++;
					break;


				case 1: 
					if(index > freeIndex)
					{
					 free(arrayB[freeIndex]);
					 freeIndex++;
					}
					break;
			}
	}

	 clock_gettime(CLOCK_REALTIME, &now); 
         double seconds = 1000*(double)((now.tv_sec+now.tv_nsec*1e-9) - (double)(tmstart.tv_sec+tmstart.tv_nsec*1e-9));    
         printf("C: %f\n\n", seconds);
}

/**
D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)

- Keep track of each malloc so that all mallocs do not exceed your total memory capacity

- Keep track of each operation so that you eventually malloc() 150 times

- Keep track of each operation so that you eventually free() all pointers

- Choose a random allocation size between 1 and 64 bytes
**/
void workLoadD()
{

}
void workLoadE(){
	 clock_gettime(CLOCK_REALTIME, &tmstart);
		
	int i;
        char* ptrA;
int j;
 for(j = 0; j<100;j++)
{

	int value = rand()%25+1;
        for(i = 0; i < 150; i++)
        {
                 ptrA = (char*)malloc(value);
                free( ptrA );
        }
}
	


	    clock_gettime(CLOCK_REALTIME, &now);
        double seconds = 1000*(double)((now.tv_sec+now.tv_nsec*1e-9) - (double)(tmstart.tv_sec+tmstart.tv_nsec*1e-9));
         printf("E: %f\n\n", seconds/100);




}
void workLoadF()
{
	 clock_gettime(CLOCK_REALTIME, &tmstart);
	int j;
	char* ptr1;
	char* ptr2;
	char* ptr3;
	
for(j=0;j<100;j++)
{
	int i;
      for(i=0; i<150;i++)
      {
	 int value = rand()%25+1;
	 ptr1 = (char*)malloc(value);
         free( ptr1 );
	 ptr2 = (char*)malloc(value);
         free( ptr2 );
	 ptr3 = (char*)malloc(value);  
         free( ptr3 );  

      }
}
	
	 clock_gettime(CLOCK_REALTIME, &now);
        double seconds = 1000*(double)((now.tv_sec+now.tv_nsec*1e-9) - (double)(tmstart.tv_sec+tmstart.tv_nsec*1e-9));
         printf("F: %f\n\n", seconds/100);

}

int main()
{	
	workLoadA();
	workLoadB();
	//workLoadC();
	//workLoadD();
	workLoadE();
	workLoadF();
	return 0;
}


/**Your memgrind.c should run all the workloads, one after the other, 100 times. It should record the run time for each workload and store it. When all 100 iterations of all the workloads have been run, memgrind.c should calculate the mean time for each workload to execute and output them in sequence.

You might find the gettimeofday(struct timeval * tv, struct timezone * tz) function in the time.h library useful.

You should run memgrind yourself and include its results in your readme.pdf. Be sure to discuss your findings, especially any interesting or unexpected results.
**/

