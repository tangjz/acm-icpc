class Solution {
public:
    int countBeautifulPairs(vector<int>& A) {
        int n = A.size(), ans = 0;
        vector<pair<int, int> > B(n);
        for(int i = 0; i < n; ++i) {
            string s = to_string(A[i]);
            B[i] = {(int)(s.front() - '0'), (int)(s.back() - '0')};
            for(int j = 0; j < i; ++j)
                ans += gcd(B[j].first, B[i].second) == 1;
        }
        return ans;
    }
};
