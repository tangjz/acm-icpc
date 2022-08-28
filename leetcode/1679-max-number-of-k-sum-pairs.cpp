class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        int ans = 0;
        for(auto &it: ctr) {
            int nxt = k - it.first;
            if(nxt == it.first) {
                ans += it.second >> 1;
            } else if(nxt > it.first) {
                auto jt = ctr.find(nxt);
                if(jt != ctr.end())
                    ans += min(it.second, jt -> second);
            }
        }
        return ans;
    }
};
