class Solution {
public:
    int sumImbalanceNumbers(vector<int>& A) {
        int n = A.size(), ans = 0;
        set<pair<int, int> > sp;
        for(int i = 0; i < n; ++i) {
            int c = 0;
            sp.clear();
            for(int j = i; j < n; ++j) {
                {
                    auto it = sp.lower_bound({A[j], j});
                    if(it != sp.end() && it != sp.begin()) {
                        auto jt = it;
                        --jt;
                        c -= (it -> first) - (jt -> first) > 1;
                    }
                }
                auto it = sp.insert({A[j], j}).first;
                if(it != sp.begin()) {
                    auto jt = it;
                    --jt;
                    c += (it -> first) - (jt -> first) > 1;
                }
                auto jt = it;
                ++jt;
                if(jt != sp.end()) {
                    c += (jt -> first) - (it -> first) > 1;
                }
                ans += c;
            }
        }
        return ans;
    }
};
