class Solution {
public:
    long long countVowels(string word) {
        const char *pat = "aeiou";
        int n = word.length();
        long long ans = 0;
        for(int i = 0; i < n; ++i) {
            int j;
            for(j = 0; j < 5; ++j)
                if(word[i] == pat[j])
                    break;
            if(j < 5)
                ans += (i + 1LL) * (n - i);
        }
        return ans;
    }
};
