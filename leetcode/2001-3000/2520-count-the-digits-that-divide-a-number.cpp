class Solution {
public:
    int countDigits(int num) {
        int ans = 0;
        for(char ch: to_string(num)) {
            int x = ch - '0';
            ans += x > 0 && num % x == 0;
        }
        return ans;
    }
};