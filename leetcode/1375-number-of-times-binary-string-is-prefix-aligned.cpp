class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
        int pos = 0, upp = 0, ans = 0;
        for(int x : light) {
            ++pos;
            upp = max(upp, x);
            ans += upp == pos;
        }
        return ans;
    }
};
