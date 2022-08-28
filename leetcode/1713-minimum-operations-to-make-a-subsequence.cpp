class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> hs;
        for(int x: target)
            hs.insert({x, (int)hs.size()});
        vector<int> que;
        for(int x: arr) {
            auto it = hs.find(x);
            if(it == hs.end())
                continue;
            int v = it -> second;
            auto jt = lower_bound(que.begin(), que.end(), v);
            if(jt == que.end()) {
                que.push_back(v);
            } else {
                *jt = v;
            }
        }
        return hs.size() - que.size();
    }
};
