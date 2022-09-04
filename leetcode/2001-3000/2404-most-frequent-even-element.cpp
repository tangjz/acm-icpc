class Solution {
public:
    int mostFrequentEven(vector<int>& nums) {
        int upp = 0;
        map<int, int> ctr;
        for(int x: nums)
            if(!(x & 1))
                upp = max(upp, ++ctr[x]);
        for(auto &it: ctr)
            if(it.second == upp)
                return it.first;
        return -1;
    }
};
