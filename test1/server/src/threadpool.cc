#include "ThreadPool.h"
#include "server.h"

void* worker_thread(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    while (true) {
        pthread_mutex_lock(&pool->queue_mutex);
        while (pool->queue_size == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->queue_not_empty, &pool->queue_mutex);
        }

        if (pool->shutdown) {
            pthread_mutex_unlock(&pool->queue_mutex);
            pthread_exit(NULL);
        }

        Task task = pool->queue[pool->queue_head];
        pool->queue_head = (pool->queue_head + 1) % MAX_QUEUE;
        pool->queue_size--;

        pthread_cond_signal(&pool->queue_not_full);
        pthread_mutex_unlock(&pool->queue_mutex);

        task.task_function(task.buffer, task.buffer_len, task.client_addr);
    }
    return NULL;
}

ThreadPool* threadpool_init() {
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    if (!pool) return NULL;

    pool->queue_size = 0;
    pool->queue_head = 0;
    pool->queue_tail = 0;
    pool->shutdown = false;

    pthread_mutex_init(&pool->queue_mutex, NULL);
    pthread_cond_init(&pool->queue_not_empty, NULL);
    pthread_cond_init(&pool->queue_not_full, NULL);

    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&pool->threads[i], NULL, worker_thread, pool);
    }

    return pool;
}

int threadpool_add_task(ThreadPool* pool,
                        void(*task_function)(void*, size_t, struct sockaddr_in),
                        void* buffer, size_t buffer_len,
                        struct sockaddr_in client_addr) {
    pthread_mutex_lock(&pool->queue_mutex);

    while (pool->queue_size == MAX_QUEUE && !pool->shutdown) {
        pthread_cond_wait(&pool->queue_not_full, &pool->queue_mutex);
    }

    if (pool->shutdown) {
        pthread_mutex_unlock(&pool->queue_mutex);
        return -1;
    }
   
    Task task = {
        .task_function = task_function,
        .buffer = buffer_copy,
        .buffer_len = buffer_len,
        .client_addr = client_addr
    };

    pool->queue[pool->queue_tail] = task;
    pool->queue_tail = (pool->queue_tail + 1) % MAX_QUEUE;
    pool->queue_size++;

    pthread_cond_signal(&pool->queue_not_empty);
    pthread_mutex_unlock(&pool->queue_mutex);

    return 0;
}
