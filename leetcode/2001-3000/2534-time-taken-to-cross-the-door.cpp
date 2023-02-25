class Solution {
public:
    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        int n = arrival.size(), tim = 0, las = 1;
        queue<int> que[2];
        vector<int> ans(n);
        for(int i = 0, j = 0; j < n; ) {
            for( ; i < n && arrival[i] <= tim; ++i)
                que[state[i]].push(i);
            int cand = -1;
            if(!que[las].empty()) {
                cand = que[las].front();
                que[las].pop();
            } else if(!que[!las].empty()) {
                cand = que[!las].front();
                que[!las].pop();
            } else {
                las = 1;
                tim = arrival[i];
                continue;
            }
            ++j;
            las = state[cand];
            ans[cand] = tim++;
        }
        return ans;
    }
};
