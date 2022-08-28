class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        int r = words.size(), n = r;
        for(auto &it: words)
            n = max(n, (int)it.size());
        auto get = [&](int x, int y) {
            return x < r && y < words[x].size() ? words[x][y] : '\0';
        };
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                if(get(i, j) != get(j, i))
                    return 0;
        return 1;
    }
};
