class PhoneDirectory {
    unordered_set<int> cand;
public:
    PhoneDirectory(int maxNumbers) {
        unordered_set<int>(maxNumbers).swap(cand);
        for(int i = 0; i < maxNumbers; ++i)
            cand.insert(i);
    }

    int get() {
        if(cand.empty())
            return -1;
        int x = *cand.begin();
        cand.erase(x);
        return x;
    }

    bool check(int number) {
        return cand.count(number);
    }

    void release(int number) {
        cand.insert(number);
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory* obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj->get();
 * bool param_2 = obj->check(number);
 * obj->release(number);
 */
