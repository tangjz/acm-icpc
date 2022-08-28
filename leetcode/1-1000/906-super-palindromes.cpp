typedef long long LL;

vector<LL> cand;

void init() {
    const int maxm = (int)1e5, maxv = (int)1e9 + 1;
    for(int i = 1; i < maxm; ++i) {
        string s = to_string(i), rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        LL x = stol(s + rev_s);
        if(x < maxv) {
            x *= x;
            string t = to_string(x), rev_t = t;
            reverse(rev_t.begin(), rev_t.end());
            if(t == rev_t)
                cand.push_back(x);
        }
        s.pop_back();
        x = stol(s + rev_s);
        if(x < maxv) {
            x *= x;
            string t = to_string(x), rev_t = t;
            reverse(rev_t.begin(), rev_t.end());
            if(t == rev_t)
                cand.push_back(x);
        }
    }
}

class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        if(cand.empty())
            init();
        int cnt = 0;
        LL L = stol(left), R = stol(right);
        for(LL x: cand)
            cnt += L <= x && x <= R;
        return cnt;
    }
};
