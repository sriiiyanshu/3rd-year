#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t x = PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t y = PTHREAD_MUTEX_INITIALIZER;  
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int readercount = 0;  
int writercount = 0;

void *reader(void *param) {
    int reader_id = *((int *)param);

   pthread_mutex_lock(&x);
    readercount++;
    if (readercount == 1) {
        pthread_mutex_lock(&y);  
   }
    pthread_mutex_unlock(&x);

    printf("Reader %d is reading data\n", reader_id);
    usleep(100000); 
    printf("Reader %d is done reading\n", reader_id);

   pthread_mutex_lock(&x);
    readercount--;
    printf("Reader %d is leaving. Remaining readers: %d\n", reader_id, readercount);
    if (readercount == 0) {
        pthread_mutex_unlock(&y); 
   }
    pthread_mutex_unlock(&x);

    return NULL;
}

void *writer(void *param) {
    int writer_id = *((int *)param);

    printf("Writer %d is trying to enter\n", writer_id);
    pthread_mutex_lock(&y);     
    printf("Writer %d is writing data\n", writer_id);
    usleep(200000);   
    printf("Writer %d is done writing\n", writer_id);
    pthread_mutex_unlock(&y);

    return NULL;
}

int main() {
    int n2, i;
    printf("Enter the number of readers and writers: ");
    scanf("%d", &n2);
    printf("\n");

    pthread_t readerthreads[n2], writerthreads[n2];
    int reader_ids[n2], writer_ids[n2];

      for (i = 0; i < n2; i++) {
        reader_ids[i] = i + 1;
        writer_ids[i] = i + 1;
        pthread_create(&readerthreads[i], NULL, reader, &reader_ids[i]);
        pthread_create(&writerthreads[i], NULL, writer, &writer_ids[i]);
    }

      for (i = 0; i < n2; i++) {
        pthread_join(readerthreads[i], NULL);
        pthread_join(writerthreads[i], NULL);
    }

    pthread_mutex_destroy(&x);
    pthread_mutex_destroy(&y);

    return 0;
}
