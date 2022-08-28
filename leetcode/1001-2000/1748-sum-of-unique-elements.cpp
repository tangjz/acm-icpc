class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        unordered_map<int, int> a;
        for(int x : nums)
            ++a[x];
        int ret = 0;
        for(auto &it : a)
            if(it.second == 1)
                ret += it.first;
        return ret;
    }
};
