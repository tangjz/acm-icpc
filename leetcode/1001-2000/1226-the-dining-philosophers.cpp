class DiningPhilosophers {
    vector<mutex> used;
public:
    DiningPhilosophers() {
        used = vector<mutex>(5);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int u = philosopher, v = (philosopher + 1) % 5;
		if(u & 1) {
            swap(u, v);
        }
        lock_guard lft(used[u]);
        lock_guard rht(used[v]);
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
    }
};
