class Solution {
public:
    int clumsy(int n) {
        int ans = 0;
        for(int i = n; i > 0; i -= 4) {
            int tmp = i < n ? -i : i;
            if(i > 1) {
                tmp *= i - 1;
                if(i > 2) {
                    tmp /= i - 2;
                    if(i > 3) {
                        tmp += i - 3;
                    }
                }
            }
            ans += tmp;
        }
        return ans;
    }
};
