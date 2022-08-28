class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int n = price.size();
        auto it = special.begin(), jt = it;
        for( ; it != special.end(); ++it) {
            int sum = 0;
            for(int i = 0; i < n; ++i) {
                if((*it)[i] > needs[i]) {
                    sum = INT_MIN;
                    break;
                }
                sum += (*it)[i] * price[i];
            }
            if((*it)[n] < sum)
                *(jt++) = *it;
        }
        special.erase(jt, special.end());
        map<vector<int>, int> dp;
        function<int()> calc = [&]() -> int {
            auto it = dp.find(needs);
            if(it != dp.end())
                return it -> second;
            int &ret = dp[needs];
            for(int i = 0; i < n; ++i)
                ret += needs[i] * price[i];
            for(auto &vec: special) {
                bool ban = 0;
                for(int i = 0; !ban && i < n; ++i)
                    ban |= vec[i] > needs[i];
                if(ban)
                    continue;
                for(int i = 0; i < n; ++i)
                    needs[i] -= vec[i];
                ret = min(ret, calc() + vec[n]);
                for(int i = 0; i < n; ++i)
                    needs[i] += vec[i];
            }
            return ret;
        };
        return calc();
    }
};
