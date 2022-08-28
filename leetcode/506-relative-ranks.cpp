class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        vector<int> que = score;
        sort(que.begin(), que.end());
        vector<string> ret;
        for(int x: score) {
            int rk = que.end() - lower_bound(que.begin(), que.end(), x);
            if(rk <= 3) {
                static const string cont[] = {"", "Gold Medal", "Silver Medal", "Bronze Medal"};
                ret.push_back(cont[rk]);
            } else {
                ret.push_back(to_string(rk));
            }
        }
        return ret;
    }
};
