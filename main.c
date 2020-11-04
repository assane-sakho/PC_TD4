#include "stdio.h"
#include "stdlib.h"
#include <pthread.h>
#include "unistd.h"
#include "string.h"

struct tampon_struct
{
   int * tampon;
   int * indexAdresse;
} *args;

pthread_mutex_t lock;

void * producer(void * arguments)
{
    pthread_mutex_lock(&lock);

    printf("\nEMISSION DES MESSAGES DANS LE TAMPON:\n");
    struct tampon_struct *args = arguments;

    args->tampon[*args->indexAdresse] = *args->indexAdresse + 1;
    printf("~ 'Bonjour%d' écrit dans le tampon\n", args->tampon[*args->indexAdresse]);
    *args->indexAdresse = *args->indexAdresse + 1;

    pthread_mutex_unlock(&lock);
}

void * consumer(void * arguments)
{
    pthread_mutex_lock(&lock);

    struct tampon_struct *args = arguments;
    printf("\nRECEPTION DES MESSAGES DU TAMPON:\n");

    int i;
    for(i = 0; i < *args->indexAdresse; i++)
    {
        printf("! 'Bonjour%d' reçu du tampon\n", args->tampon[i]);
        args->tampon[i] = 0;
    }
    *args->indexAdresse = 0;

    pthread_mutex_unlock(&lock);
}

int main()
{
    const int taille = 10;
    int * tampon = (int *)malloc(sizeof(int) * taille);

    int  index = 0;  
    int  *indexAdresse; 
    indexAdresse = &index;

    pthread_t producerThread;
    pthread_t consumerThread;

    args = malloc(sizeof(struct tampon_struct) * 1);

    args->tampon = tampon;
    args->indexAdresse = indexAdresse;

    int i;
    for(i = 0; i < 3; i++)
    {
        pthread_create(&producerThread, NULL, &producer, args);
        pthread_join(producerThread, NULL);
    }
    
    pthread_create(&consumerThread, NULL, &consumer, args);
    pthread_join(consumerThread, NULL);

    pthread_create(&producerThread, NULL, &producer, args);
    pthread_join(producerThread, NULL);

    pthread_create(&consumerThread, NULL, &consumer, args);
    pthread_join(consumerThread, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}