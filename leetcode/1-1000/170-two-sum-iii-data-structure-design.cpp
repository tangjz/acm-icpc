class TwoSum {
    typedef long long LL;
    unordered_map<int, int> ctr;
public:
    TwoSum() {
        ctr.clear();
    }
    
    void add(int number) {
        ++ctr[number];
    }
    
    bool find(int value) {
        int low = max((LL)value - INT_MAX, (LL)INT_MIN);
        int upp = min(min((LL)value - INT_MIN, ((LL)value - (value & 1)) / 2), (LL)INT_MAX);
        for(auto &it: ctr) {
            if(it.first < low || it.first > upp)
                continue;
            if(it.first + it.first == value) {
                if(it.second >= 2)
                    return 1;
            } else if(ctr.count(value - it.first)) {
                return 1;
            }
        }
        return 0;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */
