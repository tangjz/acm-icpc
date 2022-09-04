class Solution {
public:
    string capitalizeTitle(string title) {
        int n = title.size();
        for(int i = 0, j; i < n; ++i) {
            for(j = i; i < n && title[i] != ' '; ++i)
                title[i] = tolower(title[i]);
            if(j + 2 < i)
                title[j] = toupper(title[j]);
        }
        return title;
    }
};
