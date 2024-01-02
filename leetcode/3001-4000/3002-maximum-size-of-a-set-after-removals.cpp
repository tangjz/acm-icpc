class Solution {
public:
    int maximumSetSize(vector<int>& A, vector<int>& B) {
        int n = A.size(), m[3] = {};
        pair<int, int> rem = {n / 2, n / 2};
        unordered_map<int, pair<int, int> > ctr;
        for(int x: A)
            ++ctr[x].first;
        for(int x: B)
            ++ctr[x].second;
        int ans = ctr.size();
        for(auto &it: ctr) {
            rem.first -= max(it.second.first - 1, 0);
            rem.second -= max(it.second.second - 1, 0);
            ++m[!it.second.first | (!it.second.second) << 1];
        }
        rem.first = max(rem.first, 0);
        rem.second = max(rem.second, 0);
        ans -= max(rem.first + rem.second - m[0], 0);
        return ans;
    }
};
