class Solution {
public:
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        int n = heights.size(), pL = k, pR = k;
        stack<int> qL, qR;
        while(volume--) {
            for( ; pL > 0 && heights[pL] >= heights[pL - 1]; --pL)
                if(heights[pL] > heights[pL - 1])
                    qL.push(pL - 1);
            for( ; pR + 1 < n && heights[pR] >= heights[pR + 1]; ++pR)
                if(heights[pR] > heights[pR + 1])
                    qR.push(pR + 1);
            int x;
            if(!qL.empty()) {
                ++heights[x = qL.top()];
                if(heights[x] == heights[x + 1])
                    qL.pop();
                if(x > pL)
                    qL.push(x - 1);
            } else if(!qR.empty()) {
                ++heights[x = qR.top()];
                if(heights[x] == heights[x - 1])
                    qR.pop();
                if(x < pR)
                    qR.push(x + 1);
            } else {
                ++heights[k];
                if(k > pL)
                    qL.push(k - 1);
                if(k < pR)
                    qR.push(k + 1);
            }
        }
        return heights;
    }
};
