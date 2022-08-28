class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size(), ans = 1;
        map<int, int> nxt;
        vector<int> ans0(n), ans1(n);
        ans0[n - 1] = ans1[n - 1] = 1;
        nxt[arr[n - 1]] = n - 1;
        for(int i = n - 2; i >= 0; --i) {
            auto it = nxt.lower_bound(arr[i]);
            if(it != nxt.end()) {
                // printf("odd %d -> %d\n", i, it -> second);
                ans1[i] = ans0[it -> second];
            }
            it = nxt.upper_bound(arr[i]);
            if(it != nxt.begin()) {
                ans0[i] = ans1[(--it) -> second];
                // printf("even %d -> %d\n", i, it -> second);
            }
            nxt[arr[i]] = i;
            ans += ans1[i];
        }
        return ans;
    }
};
