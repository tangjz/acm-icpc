#include <semaphore.h>

class FizzBuzz {
private:
    int n;
    sem_t s[4];

    int choose(int x) {
        return (x % 3 != 0) << 1 | (x % 5 != 0);
    }
public:
    FizzBuzz(int n) {
        this->n = n;
        for(int i = 0; i < 4; ++i)
            sem_init(s + i, 0, i == choose(1));
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        for(int i = 1; i <= n; ++i)
            if(choose(i) == 1) {
                sem_wait(s + 1);
                printFizz();
                if(i + 1 <= n)
                    sem_post(s + choose(i + 1));
            }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        for(int i = 1; i <= n; ++i)
            if(choose(i) == 2) {
                sem_wait(s + 2);
                printBuzz();
                if(i + 1 <= n)
                    sem_post(s + choose(i + 1));
            }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        for(int i = 1; i <= n; ++i)
            if(choose(i) == 0) {
                sem_wait(s + 0);
                printFizzBuzz();
                if(i + 1 <= n)
                    sem_post(s + choose(i + 1));
            }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        for(int i = 1; i <= n; ++i)
            if(choose(i) == 3) {
                sem_wait(s + 3);
                printNumber(i);
                if(i + 1 <= n)
                    sem_post(s + choose(i + 1));
            }
    }
};
