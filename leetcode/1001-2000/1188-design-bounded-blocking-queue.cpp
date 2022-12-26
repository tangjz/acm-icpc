#include <semaphore.h>

class BoundedBlockingQueue {
    sem_t ctr, rem;
    queue<int> que;
public:
    BoundedBlockingQueue(int capacity) {
        sem_init(&ctr, 0, 0);
        sem_init(&rem, 0, capacity);
        queue<int>().swap(que);
    }

    void enqueue(int element) {
        sem_wait(&rem);
        que.push(element);
        sem_post(&ctr);
    }

    int dequeue() {
        sem_wait(&ctr);
        int x = que.front();
        que.pop();
        sem_post(&rem);
        return x;
    }

    int size() {
        return que.size();
    }
};
