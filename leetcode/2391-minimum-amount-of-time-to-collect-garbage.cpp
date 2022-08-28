class Solution {
public:
    int garbageCollection(vector<string>& seq, vector<int>& dt) {
        int n = seq.size();
        map<char, pair<int, int> > ctr;
        for(int i = 0; i < n; ++i)
            for(char ch: seq[i]) {
                ++ctr[ch].first;
                ctr[ch].second = i;
            }
        int ans = 0;
        for(auto &it: ctr) {
            ans += it.second.first;
            for(int j = 0; j < it.second.second; ++j)
                ans += dt[j];
        }
        return ans;
    }
};
