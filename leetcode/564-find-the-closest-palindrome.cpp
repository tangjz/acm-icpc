class Solution {
public:
    string nearestPalindromic(string s) {
        typedef long long LL;
        int len = s.size(), half = (len + 1) / 2;
        LL n = stol(s), m, val[3];
        string t, t2, rep[3];
        rep[1] = t = s.substr(0, half);
        m = stol(t);
        if(len & 1)
            rep[1].pop_back();
        reverse(rep[1].begin(), rep[1].end());
        rep[1] = t + rep[1];
        val[1] = stol(rep[1]);
        rep[0] = t2 = to_string(m - 1);
        if(t2.size() < t.size() || (len > 1 && m == 1)) {
            rep[0] = string(len - 1, '9');
        } else {
            if(len & 1)
                rep[0].pop_back();
            reverse(rep[0].begin(), rep[0].end());
            rep[0] = t2 + rep[0];
        }
        val[0] = stol(rep[0]);
        rep[2] = t2 = to_string(m + 1);
        if(t2.size() > t.size()) {
            rep[2] = string(len + 1, '0');
            rep[2].front() = rep[2].back() = '1';
        } else {
            if(len & 1)
                rep[2].pop_back();
            reverse(rep[2].begin(), rep[2].end());
            rep[2] = t2 + rep[2];
        }
        val[2] = stol(rep[2]);
        int best = -1;
        LL diff = n + 1;
        for(int i = 0; i < 3; ++i) {
            LL dt = abs(n - val[i]);
            // printf("cand %lld for %lld: %lld\n", val[i], n, dt);
            if(!dt)
                continue;
            if(dt < diff) {
                diff = dt;
                best = i;
            }
        }
        return rep[best];
    }
};
