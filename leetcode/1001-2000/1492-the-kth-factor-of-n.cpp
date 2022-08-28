class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> seq;
        for(int i = 1; i <= n; ++i)
            if(n % i == 0)
                seq.push_back(i);
        return (int)seq.size() < k ? -1 : seq[k - 1];
    }
};
