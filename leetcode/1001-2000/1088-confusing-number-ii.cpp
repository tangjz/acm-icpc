class Solution {
public:
    int confusingNumberII(int n) {
        const int maxc = 5;
        const pair<int, int> cand[maxc] = {
            {0, 0},
            {1, 1},
            {6, 9},
            {8, 8},
            {9, 6},
        };
        typedef long long LL;
        LL L = 0, R = n;
        string buf = to_string(n + 1);
        int upp = buf.size();
        vector<LL> pw = {1}, pw5 = {1};
        for(int i = 1; i <= upp + 1; ++i) {
            pw.push_back(pw.back() * 10);
            pw5.push_back(pw5.back() * 5);
        }
        pw.push_back(pw.back() * 10);
        set<pair<LL, int> > vis;
        queue<pair<LL, int> > que;
        for(int i = 0; i < maxc; ++i) {
            pair<LL, int> tmp = {(LL)cand[i].first, 1};
            if(cand[i].first == cand[i].second && tmp.first <= R && vis.insert(tmp).second)
                que.push(tmp);
            tmp = {cand[i].first * 10LL + cand[i].second, 2};
            if(tmp.first <= R && vis.insert(tmp).second)
                que.push(tmp);
        }
        int ans = 0;
        for(int i = 0; i < upp; ++i) {
            int d = buf[i] - '0';
            bool vis = 0;
            for(int j = 0; j < maxc; ++j)
                if(cand[j].first < d) {
                    ans += pw5[upp - 1 - i];
                } else if(cand[j].first == d) {
                    vis = 1;
                }
            if(!vis)
                break;
        }
        while(!que.empty()) {
            pair<LL, int> cur = que.front();
            que.pop();
            ans -= cur.first >= L && (cur.second == 1 || cur.first >= pw[cur.second - 1]);
            for(int i = 0; i < maxc; ++i) {
                pair<LL, int> nxt = {(cand[i].first * pw[cur.second] + cur.first) * 10 + cand[i].second, cur.second + 2};
                if(nxt.first <= R && nxt.second <= upp && vis.insert(nxt).second)
                    que.push(nxt);
            }
        }
        return ans;
    }
};
