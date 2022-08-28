class Solution {
public:
    int scoreOfStudents(string s, vector<int>& answers) {
        int n = s.size(), sum = 0, tmp = 0;
        vector<int> nums;
        vector<char> ops;
        for(int i = 0, j; i < n; i = j) {
            j = i + 1;
            if(s[i] == '+' || s[i] == '*') {
                ops.push_back(s[i]);
                continue;
            }
            int val = s[i] - '0';
            for( ; j < n && s[j] >= '0' && s[j] <= '9'; ++j)
                val = val * 10 + (s[j] - '0');
            nums.push_back(val);
            if(!ops.empty() && ops.back() == '*') {
                tmp *= val;
            } else {
                sum += tmp;
                tmp = val;
            }
        }
        sum += tmp;
        // printf("sum: %d\n", sum);
        n = nums.size();
        vector<vector<set<int> > > dp(n, vector<set<int> >(n));
        for(int i = 0; i < n; ++i) {
            dp[i][i].insert(nums[i]);
        }
        for(int len = 2; len <= n; ++len)
            for(int i = 0, j = len - 1; j < n; ++i, ++j) {
                for(int k = i; k < j; ++k) {
                    for(int lft: dp[i][k])
                        for(int rht: dp[k + 1][j]) {
                            int val = ops[k] == '+' ? lft + rht : lft * rht;
                            if(val <= 1000)
                                dp[i][j].insert(val);
                        }
                }
                // for(int x: dp[i][j])
                //     printf("[%d, %d]: %d\n", i, j, x);
            }
        int ans = 0;
        for(int x: answers) {
            (x == sum) && (ans += 3);
            dp[0][n - 1].count(x) && (ans += 2);
        }
        return ans;
    }
};
