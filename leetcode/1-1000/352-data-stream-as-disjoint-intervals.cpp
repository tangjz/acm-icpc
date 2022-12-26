class SummaryRanges {
    unordered_set<int> sp;
    unordered_map<int, int> pL, pR;
public:
    SummaryRanges() {
        sp.clear();
        pL.clear();
        pR.clear();
    }

    void addNum(int val) {
        if(sp.count(val))
            return;
        sp.insert(val);
        int L = val, R = val, x;
        if(sp.count(L - 1)) {
            x = pL[L - 1];
            pL.erase(L - 1);
            pR.erase(x);
            L = x;
        }
        if(sp.count(R + 1)) {
            x = pR[R + 1];
            pL.erase(x);
            pR.erase(R + 1);
            R = x;
        }
        pL.insert({R, L});
        pR.insert({L, R});
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int> > ret;
        ret.reserve(pR.size());
        for(auto &it: pR)
            ret.push_back({it.first, it.second});
        sort(ret.begin(), ret.end());
        return ret;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
