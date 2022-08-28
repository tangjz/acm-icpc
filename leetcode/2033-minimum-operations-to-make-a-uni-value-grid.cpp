class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> seq;
        for(auto &it: grid)
            for(int x: it)
                seq.push_back(x);
        sort(seq.begin(), seq.end());
        int ans = 0, mid = seq[(int)seq.size() >> 1];
        for(int v: seq) {
            int dif = abs(v - mid);
            if(dif % x > 0)
                return -1;
            ans += dif / x;
        }
        return ans;
    }
};
