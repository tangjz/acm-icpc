class Solution {
    int M, K;
    mt19937 rnd;
    vector<int>::iterator head;
public:
    Solution(int N, vector<int>& blacklist) {
        M = N - blacklist.size();
        rnd.seed(time(NULL));
        head = blacklist.begin();
        K = blacklist.end() - head;
        sort(head, head + K);
    }
    
    int pick() {
        int x = rnd() % M, L = 0, R = K;
        while(L < R) {
            int mid = (L + R) >> 1;
            if(*(head + mid) <= x + mid) {
                L = mid + 1;
            } else {
                R = mid;
            }
        }
        x += L;
        return x;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
 */
