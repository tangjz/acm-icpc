class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        int n = fronts.size();
        unordered_set<int> bad, cand;
        for(int i = 0; i < n; ++i)
            if(fronts[i] == backs[i]) {
                bad.insert(fronts[i]);
            } else {
                cand.insert(fronts[i]);
                cand.insert(backs[i]);
            }
        int ans = INT_MAX;
        for(int x: cand)
            if(!bad.count(x))
                ans = min(ans, x);
        return ans < INT_MAX ? ans : 0;
    }
};
