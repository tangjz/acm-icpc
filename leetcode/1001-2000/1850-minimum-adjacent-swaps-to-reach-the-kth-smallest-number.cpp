class Solution {
public:
    int getMinSwaps(string num, int k) {
        const int maxd = 10;
        queue<int> idx[10];
        int n = 0;
        for(char ch: num) {
            int x = ch - '0';
            idx[x].push(n++);
        }
        while(k--)
            next_permutation(num.begin(), num.end());
        vector<int> perm;
        for(char ch: num) {
            int x = ch - '0';
            perm.push_back(idx[x].front());
            idx[x].pop();
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                ans += perm[i] > perm[j];
        return ans;
    }
};
