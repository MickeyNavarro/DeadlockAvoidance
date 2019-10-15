#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//Almicke Navarro
//CST-221
//October 2, 2019
//This is my own work.

//This file is a mixture of the Monitors and Semaphores files for the in Producer and Consumer problem, but I have implemented the deadlock avoidance problem here.

/* Further file explanation
 The monitor will have the variables of mutex, full, and empty
 The mutex will only be unlocked when performing the two processes;
    it will only be unlocked once in the producer process to allow both processes to occur
    it will only be locked once in the consumer process when both processes are finished
 The full variable will keep track of if the buffer is full;
    it will be start with the value of 0 as bueffer is not full
 The empty variable will keep track of if the buffer is empty;
    it will be start with the value of 1 as buffer is empty

 */


/*Resources: https://stackoverflow.com/questions/17167949/how-to-use-timer-in-c
 https://www.tutorialspoint.com/c_standard_library/c_function_clock.htm
 */



//define buffer
#define MAX 10
int buffer[MAX];

//define a monitor using struct
typedef struct Monitor {
    
    //mutex variable (0 = locked, 1 = unlocked)
    int mutex;
    
    //full variable (0 = false, 1 = true)
    int full;
    
    //empty variable (0 = false, 1 = true)
    int empty;
    
} Monitor;

//define a counter to determine how many products are produced/yet to be consumed
int counter = 0;

//define the size of buffer
int length = sizeof(buffer)/sizeof(int);

//define the timer
clock_t start_t, end_t, total_t;

//define methods
int produce();
void put();
void *producer();
void *consumer();
void consume();
int get();

//code given by instructor
int theProduct;


//method to simply increment the product, hence creating a new product
int produce(){
    return theProduct+1;
}

//method to output that the product has been consumed
void consume(int i){
    printf("Consumed: %i\n", i);
}

//method to put the product in the buffer
void *producer(Monitor *monitor) {
    //start the timer
    start_t = clock();
    printf("Timer has been started. start_t = %ld\n",start_t);
    
    printf("/***Producing***/\n");
    
    int i;
    int total;
    
    //unlock the mutex until the producer and consumer functions are finished
    monitor->mutex = 1;
    
    printf("Mutex has been unlocked.\n");
    
    //check if monitor is NOT deemed as full
    while(monitor->full == 0){
        
        //check if the buffer is full
        if(length == counter){
            
            //if yes,
            //output
            printf("Buffer is full. No new products may be added.\n");
            
            //stop the timer
            end_t = clock();
            printf("Timer has been stopped. end_t = %ld\n",end_t);
            
            //calculate the total time that was taken
            total = end_t - start_t;
            printf("Total time (ticks): %d\n", total);
            
            //put the producer to sleep
            printf("Producer will now been put to sleep.\n");
            sleep(10); //process will temperarily stop here
            

        }
        else {
            //if no,
            //output
            printf("Buffer is not full. You may add new products.\n");
            
            //produce the new product
            i = produce();
            
            //put the product into the buffer
            put(i);
            
            //increase counter
            counter++;
        }
        
        //call the consumer process & set the monitor to full/not empty -- without this, the consumer process would end in a deadlock
        //check if timer is finished
        if (total > 100){
            //set monitor to full & not empty
            monitor->full = 1;
            monitor->empty = 0;
            //call the consumer process & pass the monitor
            consumer(monitor);
        }
    }
    return 0;
}

//method to consumer the product from the buffer
void *consumer(Monitor *monitor) {
    printf("/***Consuming***/\n");
    
    int i;
    //loop while monitor is NOT deemed as empty
    while(monitor->empty == 0){
        
        //check if buffer is full
        if (counter <= 10 && counter > 0){
            //if yes,
            //output
            printf("Buffer is full. Products may now be consumed.\n");
            
            //get the most recent product from the buffer
            i = get();
            
            //consume the product
            consume(i);
            
            //decrease the counter
            counter--;
            
            //check if the buffer is empty
            if (counter ==0){
                //if yes,
                //output
                printf("Buffer is empty. Products may NOT be consumed.\n");
                
                //set monitor to not full & empty
                monitor->full = 0;
                monitor->empty = 1;
                
                //lock the mutex and block until it becomes available
                //the consumer function is done so the mutex must be locked
                monitor->mutex = 0;
                
                //put consumer to sleep
                printf("Consumer will now been put to sleep.\n");
                sleep(20);
                
            }
        }
    }
    return 0;
}

//method to receive what the producer creates
void put(int i) {
    //set the product to the given int
    theProduct = i;
    
    //output what has been produced
    printf("Produced: %i\n", i);
    
    //put into buffer
    buffer[counter] = i;
    
    return;
}

//method to get the product from the buffer
int get() {
    //get the most recent product produced from the buffer
    int productToBeConsumed = buffer[counter];
    return productToBeConsumed;
}

int main(int argc, char *argv[]) {
    
    //create monitor struct
    Monitor monitor = {
        //lock the mutex by setting to 0
        .mutex = 0,
        //set the full attribute to 0 (false)
        .full = 0,
        //set the empty attribute to 1 (true)
        .empty = 1
    };
    
    
    //call the producer function first and pass the monitor
    producer(&monitor);
    
    return 0;
}
