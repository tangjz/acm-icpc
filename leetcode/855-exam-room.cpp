class ExamRoom {
    int n;
    set<int> sp;
    set<pair<int, int> > seg;
public:
    ExamRoom(int n) {
        this -> n = n;
    }
    
    int seat() {
        pair<int, int> ret = {INT_MAX, INT_MAX}, mid;
        if(sp.empty()) {
            ret = {n, 0};
            sp.insert(0);
            return ret.second;
        }
        int pL = *sp.begin(), pR = *sp.rbegin();
        if(pL > 0)
            ret = min(ret, {-(pL - 1), 0});
        if(pR < n - 1)
            ret = min(ret, {-(n - 2 - pR), n - 1});
        if(!seg.empty()) {
            mid = *seg.begin();
            ret = min(ret, {mid.first, mid.second - mid.first});
        }
        auto it = sp.insert(ret.second).first, jt = it;
        ++jt;
        if(jt != sp.end()) {
            int len = *jt - ret.second - 1;
            seg.insert({-((len - 1) >> 1), ret.second + 1});
        }
        if(it != sp.begin()) {
            auto kt = it;
            --kt;
            int len = ret.second - *kt - 1;
            seg.insert({-((len - 1) >> 1), *kt + 1});
            if(jt != sp.end()) {
                len = *jt - *kt - 1;
                seg.erase({-((len - 1) >> 1), *kt + 1});
            }
        }
        return ret.second;
    }
    
    void leave(int p) {
        sp.erase(p);
        if(sp.empty())
            return;
        auto it = sp.lower_bound(p);
        if(it != sp.end()) {
            int len = *it - p - 1;
            seg.erase({-((len - 1) >> 1), p + 1});
        }
        if(it != sp.begin()) {
            auto jt = it;
            --jt;
            int len = p - *jt - 1;
            seg.erase({-((len - 1) >> 1), *jt + 1});
            if(it != sp.end()) {
                len = *it - *jt - 1;
                seg.insert({-((len - 1) >> 1), *jt + 1});
            }
        }
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
