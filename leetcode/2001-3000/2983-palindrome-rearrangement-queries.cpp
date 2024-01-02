class Solution {
public:
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        static const int maxd = 26, maxn = (int)1e5 + 1;
        static int ctr[maxd | 1][maxn];
        int n = s.size(), half = n / 2;
        for(int i = 0; i < maxd; ++i) {
            char ch = 'a' + i;
            ctr[i][0] = 0;
            for(int j = 0; j < n; ++j)
                ctr[i][j + 1] = ctr[i][j] + (s[j] == ch);
        }
        vector<int> bad;
        for(int i = 0, j = n - 1; i < j; ++i, --j)
            if(s[i] != s[j])
                bad.push_back(i);
        auto checkBad = [&](int L, int R) {
            if(L > R)
                return false;
            auto it = lower_bound(bad.begin(), bad.end(), L);
            // printf("checkBad %d %d: %d\n", L, R, it != bad.end() && *it <= R);
            return it != bad.end() && *it <= R;
        };
        auto upd = [&](int rem[], int L, int R, int v) {
            if(L > R)
                return;
            for(int i = 0; i < maxd; ++i)
                rem[i] += v * (ctr[i][R + 1] - ctr[i][L]);
        };
        // auto show = [&](int rem[], string name) {
        //     printf("%s: ", name.c_str());
        //     for(int i = 0; i < maxd; ++i)
        //         printf("%d%c", rem[i], " \n"[i == maxd - 1]);
        // };
        vector<bool> ret;
        for(auto &it: queries) {
            int a = it[0], b = it[1], c = it[2], d = it[3];
            int rb = n - 1 - b, ra = n - 1 - a, rd = n - 1 - d, rc = n - 1 - c;
            if(checkBad(0, min(a, rd) - 1) || checkBad(max(b, rc) + 1, half - 1)) {
                ret.push_back(false);
                continue;
            }
            static int cur[2][maxd | 1];
            for(int i = 0; i < maxd; ++i) {
                cur[0][i] = ctr[i][b + 1] - ctr[i][a];
                cur[1][i] = ctr[i][d + 1] - ctr[i][c];
            }
            // show(cur[0], "a-b");
            // show(cur[1], "c-d");
            int L = max(a, rd), R = min(b, rc);
            if(L > R) {
                bool res = !checkBad(R + 1, L - 1);
                upd(cur[0], rb, ra, -1);
                upd(cur[1], rd, rc, -1);
                // printf("leave\n");
                // show(cur[0], "rem 0");
                // show(cur[1], "rem 1");
                for(int i = 0; res && i < maxd; ++i)
                    res &= !cur[0][i] && !cur[1][i];
                ret.push_back(res);
                continue;
            }
            int rR = n - 1 - R, rL = n - 1 - L;
            // printf("L %d R %d\n", L, R);
            upd(cur[0], rL + 1, ra, -1);
            upd(cur[0], rb, rR - 1, -1);
            upd(cur[1], R + 1, rc, -1);
            upd(cur[1], rd, L - 1, -1);
            // show(cur[0], "rem 0");
            // show(cur[1], "rem 1");
            bool res = 1;
            for(int i = 0; res && i < maxd; ++i)
                res &= cur[0][i] >= 0 && cur[1][i] >= 0 && cur[0][i] == cur[1][i];
            ret.push_back(res);
        }
        return ret;
    }
};
