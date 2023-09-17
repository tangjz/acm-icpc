class MyCalendar {
    vector<pair<int, int> > seg;
public:
    MyCalendar() {
        seg.clear();
    }

    bool book(int start, int end) {
        for(auto &it: seg) {
            int low = max(it.first, start);
            int upp = min(it.second, end);
            if(low < upp)
                return 0;
        }
        seg.push_back({start, end});
        return 1;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
