#include <pthread.h>
#include <stdio.h>

#define N 10000

struct obj {
    int x;
    pthread_mutex_t x_mutex;
};

/* this function is run by the second thread */
void *inc_x(void *x_void_ptr)
{
    /* increment x to N*/
    struct obj *o_ptr = (struct obj *)x_void_ptr;

    //printf("BEFORE\n");
pthread_mutex_lock(&o_ptr->x_mutex);
    //printf("AFTERBEFORE\n");
    for(int i = 0; i < N; i++)
        (o_ptr->x)++;
    
    //printf("BEFOREAFTER\n");
pthread_mutex_unlock(&o_ptr->x_mutex);
    //printf("AFTER\n");

    /* the function must return something - NULL will do */
    return NULL;
}

int main()
{

    struct obj o;
    o.x = 0;
    pthread_mutex_init(&o.x_mutex, NULL);

    /* show the initial values of x and y */
    printf("x: %d\n", o.x);

    /* this variable is our reference to the threads */
    pthread_t inc_x_thread[20];

    for(int i = 0; i< 20; i++){
        /* create a thread which executes inc_x(&x) */
        if(pthread_create(&(inc_x_thread[i]), NULL, inc_x, &o)) {

            fprintf(stderr, "Error creating thread\n");
            return 1;

        }
    }

    /* wait for the second thread to finish */
    for(int i = 0; i< 20; i++){
        if(pthread_join(inc_x_thread[i], NULL)) {

            fprintf(stderr, "Error joining thread\n");
            return 2;

        }
    }

    /* show the results */
    printf("x: %d\n", o.x);

    return 0;

}
