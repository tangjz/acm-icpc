class Solution {
public:
    vector<int> findLonely(vector<int>& nums) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        vector<int> ans;
        for(int x: nums)
            if(ctr[x] == 1 && !ctr.count(x - 1) && !ctr.count(x + 1))
                ans.push_back(x);
        return ans;
    }
};
