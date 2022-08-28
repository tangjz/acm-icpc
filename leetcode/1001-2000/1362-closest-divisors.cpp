class Solution {
public:
    vector<int> closestDivisors(int num) {
        pair<int, int> ans = {1, num + 1};
        auto check = [&](int u, int v) {
            if(abs(u - v) < abs(ans.first - ans.second))
                ans = {u, v};
        };
        for(int i = 2, prd; (prd = i * i) <= num + 2; ++i) {
            if((num + 2) % i == 0)
                check(i, (num + 2) / i);
            if(prd <= num + 1 && (num + 1) % i == 0)
                check(i, (num + 1) / i);
        }
        return {ans.first, ans.second};
    }
};
