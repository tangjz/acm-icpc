class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        string rep = "";
        for(int x: nums)
            rep += to_string(x);
        vector<int> ret;
        for(char ch: rep)
            ret.push_back(ch - '0');
        return ret;
    }
};
