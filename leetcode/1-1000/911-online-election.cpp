class TopVotedCandidate {
    map<int, int> res;
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        int n = times.size(), best = 0, idx = -1;
        unordered_map<int, int> ctr;
        res.clear();
        for(int i = 0; i < n; ++i) {
            int u = persons[i], c = ++ctr[u];
            if(c >= best) {
                best = c;
                idx = u;
            }
            res[times[i]] = idx;
        }
    }

    int q(int t) {
        auto it = res.upper_bound(t);
        return (--it) -> second;
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */
