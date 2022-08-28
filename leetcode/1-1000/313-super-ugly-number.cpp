class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        typedef long long LL;
        int m = primes.size();
        vector<int> seq = {1}, idx(m);
        priority_queue<pair<LL, int> > que;
        for(int i = 0; i < m; ++i)
            que.push({-1LL * seq[idx[i]] * primes[i], i});
        while(seq.size() < n) {
            seq.push_back(-que.top().first);
            while(!que.empty() && -que.top().first == seq.back()) {
                int i = que.top().second;
                que.pop();
                que.push({-1LL * seq[++idx[i]] * primes[i], i});
            }
        }
        return seq.back();
    }
};
