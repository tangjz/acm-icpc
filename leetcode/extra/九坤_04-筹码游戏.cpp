class Solution {
public:
    double chipGame(vector<int>& nums, int n) {
        map<vector<int>, double> dp;
        nums.resize(n);
        sort(nums.begin(), nums.end());
        dp[nums] = 0;
        vector<int> vec(n);
        function<double()> calc = [&]() -> double {
            auto it = dp.find(vec);
            if(it != dp.end())
                return it -> second;
            // int cnt = 0;
            // double ret = 0;
            vector<pair<double, int> > seq;
            for(int i = 0, j; i < n; i = j) {
                for(j = i; j < n && vec[i] == vec[j]; ++j);
                if(vec[j - 1] == nums[j - 1])
                    continue;
                ++vec[j - 1];
                double adt = calc();
                seq.push_back({adt, j - i});
                --vec[j - 1];
                // cnt += j - i;
                // ret += (j - i) * adt;
            }
            int cnt = 0;
            double ret = 1e100, sum = n;
            sort(seq.begin(), seq.end());
            for(auto &it: seq) {
                sum += it.first * it.second;
                cnt += it.second;
                ret = min(ret, sum / cnt);
            }
            // ret = (ret + n) / cnt;
            return dp[vec] = ret;
        };
        return calc();
    }
};
