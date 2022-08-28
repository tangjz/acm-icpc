class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        const int maxd = 26;
        int len1 = s1.size(), len2 = s2.size();
        vector<vector<int> > pR(maxd, vector<int>(len1, len1));
        for(int i = len1 - 1; i >= 0; --i) {
            pR[(int)(s1[i] - 'a')][i] = i;
            if(!i)
                continue;
            for(int j = 0; j < maxd; ++j)
                pR[j][i - 1] = pR[j][i];
        }
        vector<pair<int, int> > nxt(len1), pw(len1), tmp(len1);
        for(int i = 0; i < len1; ++i) {
            auto &[j, c] = nxt[i] = pw[i] = {i, 0};
            for(char ch: s2) {
                int o = ch - 'a';
                j = pR[o][j];
                if(j == len1) {
                    ++c;
                    j = pR[o][0];
                    if(j == len1)
                        return 0;
                }
                (++j) == len1 && (j = 0, ++c);
            }
        }
        pw.swap(nxt);
        for(int i = n2; i > 0; ) {
            if(i & 1) {
                for(int j = 0; j < len1; ++j) {
                    int k = nxt[j].first;
                    tmp[j] = pw[k];
                    tmp[j].second += nxt[j].second;
                }
                tmp.swap(nxt);
            }
            i >>= 1;
            if(i > 0) {
                for(int j = 0; j < len1; ++j) {
                    int k = pw[j].first;
                    tmp[j] = pw[k];
                    tmp[j].second += pw[j].second;
                }
                tmp.swap(pw);
            }
        }
        pair<int, int> cur = {};
        vector<vector<pair<int, int> > > seq;
        seq.push_back(move(nxt));
        while(true) {
            pair<int, int> nxt = seq.back()[cur.first];
            nxt.second += cur.second;
            if(nxt.second + (nxt.first > 0) > n1) {
                seq.pop_back();
                break;
            }
            seq.push_back(seq.back());
            auto &A = seq[seq.size() - 2], &B = seq.back();
            for(int i = 0; i < len1; ++i) {
                int j = A[i].first;
                B[i] = A[j];
                B[i].second += A[i].second;
            }
        }
        int ans = 0;
        while(!seq.empty()) {
            pair<int, int> nxt = seq.back()[cur.first];
            nxt.second += cur.second;
            if(nxt.second + (nxt.first > 0) <= n1) {
                cur = nxt;
                ans |= 1 << ((int)seq.size() - 1);
            }
            seq.pop_back();
        }
        return ans;
    }
};
