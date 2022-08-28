class Solution {
public:
    bool patternMatching(string pattern, string value) {
        int n = value.size(), ctr[2] = {};
        for(char ch: pattern)
            ++ctr[ch == 'b'];
        if(!ctr[0] || !ctr[1]) {
            int m = n / (ctr[0] + ctr[1]);
            if(m * (ctr[0] + ctr[1]) != n)
                return 0;
            return value.substr(0, n - m) == value.substr(m);
        }
        for(int i = 0; i * ctr[0] <= n; ++i) {
            int j = (n - i * ctr[0]) / ctr[1];
            if(i * ctr[0] + j * ctr[1] != n)
                continue;
            bool ok = 1;
            int sta = 0, len[2] = {i, j};
            string pat[2];
            for(char ch: pattern) {
                int o = ch == 'b';
                if(!len[o])
                    continue;
                if(pat[o] == "") {
                    pat[o] = value.substr(sta, len[o]);
                } else if(pat[o] != value.substr(sta, len[o])) {
                    ok = 0;
                    break;
                }
                sta += len[o];
            }
            if(ok && pat[0] != pat[1])
                return 1;
        }
        return 0;
    }
};
