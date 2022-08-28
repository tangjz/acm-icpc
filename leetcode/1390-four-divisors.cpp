class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;
        for(int x : nums) {
            int cnt = 1, sum = 1;
            for(int i = 2, tmp = x; i <= tmp && cnt <= 4; ++i) {
                if(i * i > tmp)
                    i = tmp;
                if(tmp % i > 0)
                    continue;
                int pw = 1, ex = 0, sm = 1;
                for( ; tmp % i == 0; tmp /= i, pw *= i, ++ex, sm += pw);
                cnt *= ex + 1;
                sum *= sm;
            }
            if(cnt == 4)
                ans += sum;
        }
        return ans;
    }
};
