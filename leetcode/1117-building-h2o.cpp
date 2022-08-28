#include <semaphore.h>

class H2O {
    mutex lock;
    bool typ;
    sem_t s_h, s_o;
    
    void check() {
        lock_guard cur(lock);
        typ = !typ;
        if(typ) {
            sem_post(&s_h);
        } else {
            sem_post(&s_o);
        }
    }
    
public:
    H2O() {
        typ = 0;
        sem_init(&s_h, 0, 0);
        sem_init(&s_o, 0, 1);
    }

    void hydrogen(function<void()> releaseHydrogen) {
        sem_wait(&s_h);
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        check();
    }

    void oxygen(function<void()> releaseOxygen) {
        sem_wait(&s_o);
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        sem_post(&s_h);
    }
};
