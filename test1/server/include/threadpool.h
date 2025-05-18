#pragma once

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <netinet/in.h>
#include <queue>
#include <thread>
#include <cstring>
#include <vector>
#include <pthread.h>

#define MAX_QUEUE 64
#define MAX_THREADS 4


typedef struct{
    void (*task_function) (void*, size_t, struct sockaddr_in);
    void *buffer;
    Server* server;
    std::string message;
    size_t buffer_len;
    struct sockaddr_in client_addr;
} Task;


typedef struct{
    Task queue[MAX_QUEUE];
    int queue_size;
    int queue_head;
    int queue_tail;
    pthread_mutex_t queue_mutex;
    pthread_cond_t queue_not_empty;
    pthread_cond_t queue_not_full;
    pthread_t threads[MAX_THREADS];
    bool shutdown;
}ThreadPool;
