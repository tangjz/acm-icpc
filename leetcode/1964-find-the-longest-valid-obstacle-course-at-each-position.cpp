class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        vector<int> best, ret;
        best.push_back(0);
        for(int x: obstacles) {
            int p = upper_bound(best.begin(), best.end(), x) - best.begin();
            if(p == best.size()) {
                best.push_back(x);
            } else {
                best[p] = x;
            }
            ret.push_back(p);
        }
        return ret;
    }
};
