#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;
pthread_mutex_t mutex;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&rw_mutex);
        pthread_mutex_unlock(&mutex);

        printf("Reader %d: %d\n", reader_id, shared_data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&rw_mutex);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    for (int i = 0; i < 10; i++) {
        sem_wait(&rw_mutex);
        shared_data++;
        printf("Writer %d: %d\n", writer_id, shared_data);
        sleep(2);
        sem_post(&rw_mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    int num_readers = 3, num_writers = 2;
    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    sem_init(&rw_mutex, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < num_readers; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < num_writers; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);

    return 0;
}

