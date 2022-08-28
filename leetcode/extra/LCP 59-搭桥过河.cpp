class Solution {
public:
    long long buildBridge(int num, vector<vector<int>>& wood) {
        typedef long long LL;
        int pre, cur;
        LL dL = 0, dR = 0, ans = 0;
        priority_queue<LL> qL;
        priority_queue<LL, vector<LL>, greater<> > qR;
        for(auto &it: wood) {
            cur = (it[1] -= it[0]);
            if(qL.empty()) {
                qL.push(it[0]);
                qR.push(it[0]);
                pre = cur;
                continue;
            }
            LL cL = qL.top() + (dL -= cur), cR = qR.top() + (dR += pre);
            if(it[0] < cL) {
                ans += cL - it[0];
                qL.pop();
                qL.push(it[0] - dL);
                qL.push(it[0] - dL);
                qR.push(cL - dR);
            } else if(it[0] > cR) {
                ans += it[0] - cR;
                qR.pop();
                qR.push(it[0] - dR);
                qR.push(it[0] - dR);
                qL.push(cR - dL);
            } else {
                qL.push(it[0] - dL);
                qR.push(it[0] - dR);
            }
            pre = cur;
        }
        return ans;
    }
};
