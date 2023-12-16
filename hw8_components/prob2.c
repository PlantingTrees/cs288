
#include <stdio.h>
#include <math.h>
#include <pthread.h>
int no_of_terms;
int no_of_thread;
long double gPi = 0.0; //  global accumulator for areas computed
pthread_mutex_t PILock;

void *calculate_pi(void *pArg)
{
    int thread_number = *((int *)pArg);
    double height = 2.0 / no_of_terms;
    long double partial_sum = 0.0L, height_cal;
    for (int i = thread_number; i < no_of_terms; i += no_of_thread)
    {
        height_cal = -1 + (i + 0.5f) * height;
        partial_sum += sqrt(1.0 - height_cal * height_cal) * height;
    }
    pthread_mutex_lock(&PILock);
    gPi += partial_sum;
    pthread_mutex_unlock(&PILock);
    return 0;
}

int main(int argc, char **argv)
{   
    sscanf(argv[1], "%d", &no_of_terms);
    sscanf(argv[2], "%d", &no_of_thread);
    pthread_t thread_array[no_of_thread];
    int thread_number_array[no_of_thread], i;
    pthread_mutex_init(&PILock, NULL);
    for (i = 0; i < no_of_thread; ++i)
    {
        thread_number_array[i] = i;
        pthread_create(&thread_array[i], NULL, calculate_pi,  (void *)&thread_number_array[i]);
    }
    for (i = 0; i < no_of_thread; ++i)
    {
        pthread_join(thread_array[i], NULL);
    }
    gPi *= 2.0;
    printf("Computed value of Pi:  %Lf\n", gPi);
    pthread_mutex_destroy(&PILock);
    return 0;
}



