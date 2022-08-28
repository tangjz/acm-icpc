class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int const &u, int const &v) {
            string lft = to_string(u), rht = to_string(v);
            return lft + rht > rht + lft;
        });
        string ret = "";
        for(int x : nums)
            ret += to_string(x);
        int pos = 0, len = (int)ret.length();
        for( ; pos < len && ret[pos] == '0'; ++pos);
        return pos < len ? ret.substr(pos, len - pos) : "0";
    }
};
