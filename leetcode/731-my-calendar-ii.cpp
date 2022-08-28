class MyCalendarTwo {
    int n;
    vector<int> pos, ctr;
    void addPos(int x) {
        int i = lower_bound(pos.begin(), pos.end(), x) - pos.begin();
        if(i < n && pos[i] == x)
            return;
        // pos[i - 1] < x < pos[i]
        ++n;
        pos.push_back(x);
        rotate(pos.begin() + i, pos.end() - 1, pos.end());
        ctr.push_back(ctr[i - 1]);
        rotate(ctr.begin() + i, ctr.end() - 1, ctr.end());
    }
public:
    MyCalendarTwo() {
        n = 2;
        pos = {0, (int)1e9};
        ctr = {0, 0};
    }
    
    bool book(int start, int end) {
        for(int i = 0; i + 1 < n; ++i) {
            if(max(pos[i], start) >= min(pos[i + 1], end))
                continue;
            if(ctr[i] == 2)
                return false;
        }
        addPos(start);
        addPos(end);
        // puts("");
        for(int i = 0; i + 1 < n; ++i) {
            // printf("[%d, %d): %d + %d\n", pos[i], pos[i + 1], ctr[i], max(pos[i], start) < min(pos[i + 1], end));
            if(max(pos[i], start) >= min(pos[i + 1], end))
                continue;
            ++ctr[i];
        }
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
