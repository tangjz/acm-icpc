class Solution {
public:
    bool divideArray(vector<int>& nums) {
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        for(auto &it: ctr)
            if(it.second & 1)
                return 0;
        return 1;
    }
};
