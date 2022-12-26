#include <semaphore.h>

class FooBar {
private:
    int n;
    sem_t s_f, s_b;

public:
    FooBar(int n) {
        this->n = n;
        sem_init(&s_f, 0, 1);
        sem_init(&s_b, 0, 0);
    }

    void foo(function<void()> printFoo) {

        for (int i = 0; i < n; i++) {
            sem_wait(&s_f);
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            sem_post(&s_b);
        }
    }

    void bar(function<void()> printBar) {

        for (int i = 0; i < n; i++) {
            sem_wait(&s_b);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            if(i + 1 < n)
                sem_post(&s_f);
        }
    }
};
