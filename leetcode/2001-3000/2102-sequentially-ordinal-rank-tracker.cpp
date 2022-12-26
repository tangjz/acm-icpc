class SORTracker {
    typedef pair<int, string> pk;
    int ctr;
    set<pk> lft, rht;
public:
    SORTracker() {
        ctr = 0;
        lft.clear();
        rht.clear();
    }

    void add(string name, int score) {
        rht.insert({-score, name});
        if(!ctr)
            return;
        pk u = *lft.rbegin(), v = *rht.begin();
        if(u > v) {
            lft.erase(u);
            lft.insert(v);
            rht.erase(v);
            rht.insert(u);
        }
    }

    string get() {
        pk state = *rht.begin();
        string ans = state.second;
        ++ctr;
        lft.insert(state);
        rht.erase(state);
        return ans;
    }
};

/**
 * Your SORTracker object will be instantiated and called as such:
 * SORTracker* obj = new SORTracker();
 * obj->add(name,score);
 * string param_2 = obj->get();
 */
