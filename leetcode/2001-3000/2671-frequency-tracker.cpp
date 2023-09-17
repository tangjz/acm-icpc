class FrequencyTracker {
    unordered_map<int, int> ctr;
    vector<int> freq;

    void upd(int c, int v) {
        if(!c || !v)
            return;
        if(c >= freq.size())
            freq.resize(c + 1);
        freq[c] += v;
    }
public:
    FrequencyTracker() {
        ctr.clear();
        freq.resize(1);
    }

    void add(int x) {
        upd(ctr[x], -1);
        upd(++ctr[x], 1);
    }

    void deleteOne(int x) {
        auto it = ctr.find(x);
        if(it == ctr.end() || !(it -> second))
            return;
        upd(it -> second, -1);
        upd(--(it -> second), 1);
        // assert(ctr[x] == it -> second);
    }

    bool hasFrequency(int f) {
        return f < freq.size() && freq[f];
    }
};

/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */
