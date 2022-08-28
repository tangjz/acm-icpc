class Solution {
public:
    int getKthMagicNumber(int k) {
        static const int maxp = 3, pr[maxp] = {3, 5, 7};
        static int idx[maxp] = {};
        static vector<long long> seq = {1};
        while((int)seq.size() < k) {
            long long nxt = LLONG_MAX;
            for(int i = 0; i < maxp; ++i)
                nxt = min(nxt, seq[idx[i]] * pr[i]);
            seq.push_back(nxt);
            for(int i = 0; i < maxp; ++i)
                idx[i] += seq[idx[i]] * pr[i] == nxt;
        }
        return seq[k - 1];
    }
};
