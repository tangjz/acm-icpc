class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        typedef long long LL;
        vector<pair<int, int> > vec;
        for(int i = 0; i < n; ++i)
            vec.push_back(make_pair(efficiency[i], speed[i]));
        sort(vec.begin(), vec.end());
        reverse(vec.begin(), vec.end());
        LL sum = 0, ans = 0;
        priority_queue<int> Q;
        for(int i = 0; i < n; ++i) {
            auto &it = vec[i];
            sum += it.second;
            LL tmp = sum;
            if(i >= k)
                tmp += Q.top();
            ans = max(ans, tmp * it.first);
            Q.push(-it.second);
            if(i >= k) {
                sum += Q.top();
                Q.pop();
            }
        }
        return ans % ((int)1e9 + 7);
    }
};
