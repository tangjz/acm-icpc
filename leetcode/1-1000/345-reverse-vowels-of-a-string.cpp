class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> sp = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int n = s.size();
        for(int i = 0, j = n - 1; i < j; ) {
            for( ; i < j && !sp.count(s[i]); ++i);
            for( ; i < j && !sp.count(s[j]); --j);
            if(i < j)
                swap(s[i++], s[j--]);
        }
        return s;
    }
};
