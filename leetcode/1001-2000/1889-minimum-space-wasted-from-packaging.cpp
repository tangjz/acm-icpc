class Solution {
public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        int n = packages.size();
        sort(packages.begin(), packages.end());
        vector<long long> psum = {0};
        for(int x: packages)
            psum.push_back(psum.back() + x);
        long long ans = LLONG_MAX;
        for(auto &seq: boxes) {
            sort(seq.begin(), seq.end());
            if(seq.back() < packages.back())
                continue;
            long long tmp = 0;
            int pos = 0;
            for(int x: seq) {
                int nxt = upper_bound(packages.begin(), packages.end(), x) - packages.begin();
                tmp += 1LL * x * (nxt - pos) - (psum[nxt] - psum[pos]);
                if(nxt == n)
                    break;
                pos = nxt;
            }
            ans = min(ans, tmp);
        }
        return ans < LLONG_MAX ? ans % ((int)1e9 + 7) : -1;
    }
};
