class Solution {
public:
    int differenceOfSum(vector<int>& nums) {
        int a = 0, b = 0;
        for(int x: nums) {
            a += x;
            for(char ch: to_string(x))
                b += ch - '0';
        }
        return abs(a - b);
    }
};