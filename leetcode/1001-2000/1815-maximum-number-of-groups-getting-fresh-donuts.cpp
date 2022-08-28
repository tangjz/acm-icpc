class Solution {
    map<vector<int>, int> Hash;
    int dp(vector<int> &cur, int sum, int cnt) {
        if(!cnt)
            return 0;
        auto it = Hash.find(cur);
        if(it != Hash.end())
            return it -> second;
        int rem = sum % cur.size();
        int &ret = Hash[cur];
        int pos = 0;
        for(int &x: cur) {
            if(x > 0) {
                --x;
                ret = max(ret, dp(cur, sum - pos, cnt - 1) + (pos == rem));
                ++x;
            }
            ++pos;
        }
        return ret;
    }
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> vec(batchSize);
        for(int x: groups)
            ++vec[x % batchSize];
        int adt = vec[0], pos = 0, sum = 0, cnt = 0;
        vec[0] = 0;
        for(int x: vec) {
            sum += x * pos;
            cnt += x;
            ++pos;
        }
        return adt + dp(vec, sum, cnt);
    }
};
