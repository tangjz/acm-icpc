class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        if(s1 > s2)
            s1.swap(s2);
        int n = (int)s1.length();
        for(int i = 0; i < n; ++i)
            if(s1[i] > s2[i])
                return 0;
        return 1;
    }
};
