class Solution {
    int N, M;
    vector<int> ctr;
    vector<vector<int> >::iterator head;
    mt19937 rnd;
public:
    Solution(vector<vector<int>>& rects) {
        head = rects.begin();
        N = rects.end() - head;
        M = 0;
        vector<int>().swap(ctr);
        for(auto &it : rects) {
            M += (it[2] - it[0] + 1) * (it[3] - it[1] + 1);
            ctr.push_back(M);
        }
        rnd.seed(time(NULL));
    }
    
    vector<int> pick() {
        int pos = rnd() % M, L = 0, R = N - 1;
        while(L < R) {
            int mid = (L + R) >> 1;
            if(pos < ctr[mid]) {
                R = mid;
            } else {
                L = mid + 1;
            }
        }
        if(L > 0)
            pos -= ctr[L - 1];
        auto &it = *(head + L);
        int width = it[3] - it[1] + 1;
        return {it[0] + (pos / width), it[1] + (pos % width)};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */
