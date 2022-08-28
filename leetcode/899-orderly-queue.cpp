class Solution {
    int getMinRep(string const &s) {
        int n = s.size(), i = 0, j = 1, k = 0, dt;
        while(i < n && j < n && k < n) {
            dt = s[(i + k) % n] - s[(j + k) % n];
            if(!dt) {
                ++k;
            } else {
                (dt < 0 ? j : i) += k + 1;
                j += i == j;
                k = 0;
            }
        }
        return min(i, j);
    }
public:
    string orderlyQueue(string S, int K) {
        if(K > 1) {
            sort(S.begin(), S.end());
        } else {
            int sta = getMinRep(S);
            S = S.substr(sta) + S.substr(0, sta);
        }
        return S;
    }
};
