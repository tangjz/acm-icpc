class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& seq) {
        int n = s.size(), m = p.size();
        vector<int> ban(n);
        int L = 0, R = seq.size();
        while(L < R) {
            int M = (L + R + 1) >> 1;
            for(int i = 0; i < M; ++i)
                ban[seq[i]] = 1;
            int pos = 0;
            for(int i = 0; i < n && pos < m; ++i) {
                if(ban[i])
                    continue;
                pos += s[i] == p[pos];
            }
            for(int i = 0; i < M; ++i)
                ban[seq[i]] = 0;
            if(pos == m) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
