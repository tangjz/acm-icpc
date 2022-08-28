class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        auto it = nums.begin();
        string ret = "";
        for(int i = 0; i < n; ++i)
            ret += '0';
        for(int i = 0; i < (1 << n); ++i) {
            if(it == nums.end() || ret != *it)
                return ret;
            while(it != nums.end() && ret == *it)
                ++it;
            for(int j = n - 1; j >= 0; --j)
                if(ret[j] == '0') {
                    ret[j] = '1';
                    break;
                } else {
                    ret[j] = '0';
                }
        }
        return ret;
    }
};
