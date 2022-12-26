class MyCalendarThree {
    int res;
    vector<pair<int, int> > seg;
public:
    MyCalendarThree() {
        res = 0;
        vector<pair<int, int> >().swap(seg);
    }

    int getIndex(int time) {
        int size = (int)seg.size();
        for(int i = 0; i < size; ++i) {
            if(seg[i].first < time)
                continue;
            if(seg[i].first > time) {
                seg.push_back(make_pair(0, 0));
                for(int j = size; j > i; --j)
                    seg[j] = seg[j - 1];
                seg[i] = make_pair(time, i > 0 ? seg[i - 1].second : 0);
            }
            return i;
        }
        seg.push_back(make_pair(time, 0));
        return size;
    }

    int book(int start, int end) {
        for(start = getIndex(start), end = getIndex(end); start < end; ++start)
            res = max(res, ++seg[start].second);
        return res;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */
