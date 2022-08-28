class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size();
        set<int> rem;
        map<int, vector<int> > events;
        for(int i = 0; i < n; ++i) {
            rem.insert(i);
            for(int j = 0; j < 2; ++j)
                events[times[i][j]].push_back(j * n + i);
        }
        vector<int> pos(n, -1);
        for(auto &it: events) {
            auto &jt = it.second;
            sort(jt.begin(), jt.end(), greater<int>());
            for(int v: jt) {
                int i = v % n, j = v / n;
                if(j > 0) {
                    rem.insert(pos[i]);
                } else {
                    pos[i] = *rem.begin();
                    rem.erase(pos[i]);
                }
                if(i == targetFriend)
                    return pos[i];
            }
        }
        return -1;
    }
};
