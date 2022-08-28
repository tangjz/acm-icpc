class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> Hash;
        for(int x : nums)
            Hash.insert(x);
        int ans = 0;
        for(int x : nums) {
            if(Hash.find(x - 1) != Hash.end())
                continue;
            int tmp = 1;
            while(Hash.find(x + tmp) != Hash.end())
                ++tmp;
            ans = max(ans, tmp);
        }
        return ans;
    }
};
