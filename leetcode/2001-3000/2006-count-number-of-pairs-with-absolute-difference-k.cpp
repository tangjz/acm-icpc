class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ctr[x] += 1;
        int ans = 0;
        for(auto &it: ctr) {
            auto jt = ctr.find(it.first + k);
            if(jt == ctr.end())
                continue;
            ans += it.second * (jt -> second);
        }
        return ans;
    }
};
