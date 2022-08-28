class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int ans = 0, pL = INT_MAX, pR = INT_MIN;
        for(auto &vec: arrays) {
            int qL = vec.back(), qR = qL;
            for(int &x: vec)
                if(x < qL) {
                    qL = x;
                } else if(x > qR) {
                    qR = x;
                }
            vec = {qL, qR};
            if(qL < pR)
                ans = max(ans, pR - qL);
            if(qR > pL)
                ans = max(ans, qR - pL);
            pL = min(pL, qL);
            pR = max(pR, qR);
        }
        reverse(arrays.begin(), arrays.end());
        pL = INT_MAX;
        pR = INT_MIN;
        for(auto &vec: arrays) {
            int qL = vec.front(), qR = vec.back();
            if(qL < pR)
                ans = max(ans, pR - qL);
            if(qR > pL)
                ans = max(ans, qR - pL);
            pL = min(pL, qL);
            pR = max(pR, qR);
        }
        return ans;
    }
};
