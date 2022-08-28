class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int n = (int)nums.size();
        int pos = 0;
        for(auto &it : groups) {
            int m = (int)it.size();
            bool matched = 0;
            for( ; pos < n; ++pos) {
                if(pos + m > n)
                    continue;
                matched = 1;
                auto jt = nums.begin() + pos;
                for(auto &x : it) {
                    if(x != *(jt++)) {
                        matched = 0;
                        break;
                    }
                }
                if(matched) {
                    pos += m;
                    break;
                }
            }
            if(!matched)
                return false;
        }
        return true;
    }
};
