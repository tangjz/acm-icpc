class Solution {
public:
    double calculateTax(vector<vector<int>>& brackets, int income) {
        sort(brackets.begin(), brackets.end(), greater<>());
        int las = 0;
        double ans = 0;
        while(!brackets.empty()) {
            int cur = brackets.back()[0];
            int per = brackets.back()[1];
            brackets.pop_back();
            ans += max(min(income, cur) - las, 0) * per;
            las = cur;
        }
        return ans / 100;
    }
};
