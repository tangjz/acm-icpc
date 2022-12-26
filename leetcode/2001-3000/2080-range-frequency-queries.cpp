class RangeFreqQuery {
    map<int, vector<int> > pos;
public:
    RangeFreqQuery(vector<int>& arr) {
        int n = arr.size();
        pos.clear();
        for(int i = 0; i < n; ++i)
            pos[arr[i]].push_back(i);
    }

    int query(int right, int value) {
        if(!pos.count(value))
            return 0;
        vector<int> &cur = pos[value];
        return upper_bound(cur.begin(), cur.end(), right) - cur.begin();
    }

    int query(int left, int right, int value) {
        return query(right, value) - query(left - 1, value);
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
