#include <semaphore.h>

class Foo {
    sem_t s[3];
public:
    Foo() {
        for(int i = 0; i < 3; ++i)
            sem_init(s + i, 0, i == 0);
    }

    void first(function<void()> printFirst) {
        sem_wait(s + 0);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        sem_post(s + 1);
    }

    void second(function<void()> printSecond) {
        sem_wait(s + 1);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        sem_post(s + 2);
    }

    void third(function<void()> printThird) {
        sem_wait(s + 2);
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
