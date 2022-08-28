class CountIntervals {
    int cnt;
    set<pair<int, int> > seg;

    void addRange(int left, int right) {
        if(queryRange(left, right))
            return;
        removeRange(left, right);
        auto it = seg.upper_bound({left, INT_MAX});
        if(it != seg.end() && it -> first <= right) {
            right = it -> second;
            // printf("erase %d %d\n", it -> first, it -> second);
            cnt -= it -> second - it -> first;
            seg.erase(it);
            it = seg.upper_bound({left, INT_MAX});
        }
        if(it != seg.begin() && (--it) -> second >= left) {
            left = it -> first;
            // printf("erase %d %d\n", it -> first, it -> second);
            cnt -= it -> second - it -> first;
            seg.erase(it);
        }
        // printf("insert %d %d\n", left, right);
        cnt += right - left;
        seg.insert({left, right});
    }
    
    bool queryRange(int left, int right) {
        auto it = seg.upper_bound({left, INT_MAX});
        return it != seg.begin() && (--it) -> second >= right;
    }
    
    void removeRange(int left, int right) {
        while(true) {
            auto it = seg.upper_bound({left, INT_MAX});
            if(it == seg.end() || it -> first >= right)
                break;
            pair<int, int> rem = {right, it -> second};
            // printf("erase %d %d\n", it -> first, it -> second);
            cnt -= it -> second - it -> first;
            seg.erase(it);
            if(rem.first < rem.second) {
                // printf("insert %d %d\n", rem.first, rem.second);
                cnt += rem.second - rem.first;
                seg.insert(rem);
                break;
            }
        }
        auto it = seg.upper_bound({left, INT_MAX});
        if(it != seg.begin() && (--it) -> second > left) {
            pair<int, int> rem1 = {it -> first, left};
            pair<int, int> rem2 = {right, it -> second};
            // printf("erase %d %d\n", it -> first, it -> second);
            cnt -= it -> second - it -> first;
            seg.erase(it);
            if(rem1.first < rem1.second) {
                // printf("insert %d %d\n", rem1.first, rem1.second);
                cnt += rem1.second - rem1.first;
                seg.insert(rem1);
            }
            if(rem2.first < rem2.second) {
                // printf("insert %d %d\n", rem2.first, rem2.second);
                cnt += rem2.second - rem2.first;
                seg.insert(rem2);
            }
        }
    }

public:
    CountIntervals() {
        cnt = 0;
        seg.clear();
    }
    
    void add(int left, int right) {
        addRange(left, right + 1);
    }
    
    int count() {
        return cnt;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
