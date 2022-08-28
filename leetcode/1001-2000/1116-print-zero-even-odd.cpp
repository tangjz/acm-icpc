#include <semaphore.h>

class ZeroEvenOdd {
private:
    int n;
    sem_t s_zero, s_even, s_odd;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        sem_init(&s_zero, 0, 1);
        sem_init(&s_even, 0, 0);
        sem_init(&s_odd, 0, 0);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for(int i = 1; i <= n; ++i) {
            sem_wait(&s_zero);
            printNumber(0);
            sem_post(i & 1 ? &s_odd : &s_even);
        }
    }

    void even(function<void(int)> printNumber) {
        for(int i = 2; i <= n; i += 2) {
            sem_wait(&s_even);
            printNumber(i);
            sem_post(&s_zero);
        }
    }

    void odd(function<void(int)> printNumber) {
        for(int i = 1; i <= n; i += 2) {
            sem_wait(&s_odd);
            printNumber(i);
            sem_post(&s_zero);
        }
    }
};
