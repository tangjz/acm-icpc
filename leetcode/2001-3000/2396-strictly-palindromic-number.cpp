class Solution {
public:
    bool isStrictlyPalindromic(int n) {
        vector<int> seq;
        for(int i = 2; i <= n - 2; ++i) {
            for(int j = n; j > 0; seq.push_back(j % i), j /= i);
            for(int j = 0, k = (int)seq.size() - 1; j < k; ++j, --k)
                if(seq[j] != seq[k])
                    return 0;
            seq.clear();
        }
        return 1;
    }
};
