class Solution {
public:
    int countPairs(vector<int>& seq) {
        int mx = 0;
        unordered_map<int, int> ctr;
        for(int x: seq) {
            mx = max(mx, x);
            ++ctr[x];
        }
        long long ans = 0;
        for(int x: seq) {
            --ctr[x];
            for(int pw = 1; pw <= mx + x; pw <<= 1) {
                if(pw < x)
                    continue;
                auto it = ctr.find(pw - x);
                if(it != ctr.end())
                    ans += it -> second;
            }
            ++ctr[x];
        }
        return ans / 2 % ((int)1e9 + 7);
    }
};
