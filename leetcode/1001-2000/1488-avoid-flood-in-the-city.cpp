class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = (int)rains.size();
        vector<int> ret, pos;
        vector<vector<int> > rht(n, vector<int>());
        unordered_map<int, int> las;
        for(int i = 0; i < n; ++i) {
            int cur = rains[i];
            if(!cur) {
                ret.push_back(1);
                pos.push_back(i);
            } else {
                if(las.count(cur))
                    rht[las[cur]].push_back(i);
                las[cur] = i;
                ret.push_back(-1);
            }
        }
        priority_queue<int> que;
        int L = 0;
        for(int x : pos) {
            for( ; L < x; ++L)
                for(int R : rht[L])
                    que.push(-R);
            if(!que.empty()) {
                int R = -que.top();
                if(R < x)
                    return vector<int>();
                que.pop();
                ret[x] = rains[R];
            }
        }
        for( ; L < n; ++L)
            for(int R : rht[L])
                que.push(-R);
        return que.empty() ? ret : vector<int>();
    }
};
