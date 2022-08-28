class Solution {
public:
    double calculateMaxInfoGain(vector<double>& petal_length, vector<string>& species) {
        int n = species.size();
        if(n <= 1)
            return 0;
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return petal_length[u] < petal_length[v];
        });
        vector<double> lg2(n), pre(n), suf(n);
        double sum = 0;
        unordered_map<string, int> ctr;
        for(int i = 0; i < n; ++i) {
            lg2[i] = log2(i + 1);
            int u = ord[i];
            int &cnt = ctr[species[u]];
            if(cnt > 0) {
                sum -= cnt * lg2[cnt - 1];
            }
            ++cnt;
            sum += cnt * lg2[cnt - 1];
            pre[i] = max(lg2[i] - sum / (i + 1), 0.0);
        }
        sum = 0;
        ctr.clear();
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i];
            int &cnt = ctr[species[u]];
            if(cnt > 0) {
                sum -= cnt * lg2[cnt - 1];
            }
            ++cnt;
            sum += cnt * lg2[cnt - 1];
            suf[i] = max(lg2[n - 1 - i] - sum / (n - i), 0.0);
        }
        double ans = 0.0;
        for(int i = 1; i < n; ++i) {
            if(petal_length[ord[i - 1]] == petal_length[ord[i]])
                continue;
            double tmp = pre[n - 1] * n - pre[i - 1] * i - suf[i] * (n - i);
            ans = max(ans, tmp);
        }
        return ans / n;
    }
};
