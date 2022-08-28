class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(slots1.begin(), slots1.end());
        sort(slots2.begin(), slots2.end());
        auto it = slots1.begin(), jt = slots2.begin();
        while(it != slots1.end() && jt != slots2.end()) {
            int L = max((*it)[0], (*jt)[0]), R = min((*it)[1], (*jt)[1]);
            if(R - L >= duration)
                return {L, L + duration};
            (*it)[1] < (*jt)[1] ? ++it : ++jt;
        }
        return {};
    }
};
