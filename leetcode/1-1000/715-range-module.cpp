class RangeModule {
    set<pair<int, int> > seg;
public:
    RangeModule() {
        seg.clear();
    }

    void addRange(int left, int right) {
        if(queryRange(left, right))
            return;
        removeRange(left, right);
        auto it = seg.upper_bound({left, INT_MAX});
        if(it != seg.end() && it -> first <= right) {
            right = it -> second;
            // printf("erase %d %d\n", it -> first, it -> second);
            seg.erase(it);
            it = seg.upper_bound({left, INT_MAX});
        }
        if(it != seg.begin() && (--it) -> second >= left) {
            left = it -> first;
            // printf("erase %d %d\n", it -> first, it -> second);
            seg.erase(it);
        }
        // printf("insert %d %d\n", left, right);
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
            seg.erase(it);
            if(rem.first < rem.second) {
                // printf("insert %d %d\n", rem.first, rem.second);
                seg.insert(rem);
                break;
            }
        }
        auto it = seg.upper_bound({left, INT_MAX});
        if(it != seg.begin() && (--it) -> second > left) {
            pair<int, int> rem1 = {it -> first, left};
            pair<int, int> rem2 = {right, it -> second};
            // printf("erase %d %d\n", it -> first, it -> second);
            seg.erase(it);
            if(rem1.first < rem1.second) {
                // printf("insert %d %d\n", rem1.first, rem1.second);
                seg.insert(rem1);
            }
            if(rem2.first < rem2.second) {
                // printf("insert %d %d\n", rem2.first, rem2.second);
                seg.insert(rem2);
            }
        }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
