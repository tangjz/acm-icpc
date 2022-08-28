class Solution {
public:
    bool isPathCrossing(string path) {
        const char *pat = "NSEW";
        const int d[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        vector<pair<int, int> > seq;
        seq.push_back({0, 0});
        for(char ch : path)
            for(int i = 0; i < 4; ++i)
                if(pat[i] == ch) {
                    pair<int, int> tmp = seq.back();
                    tmp.first += d[i][0];
                    tmp.second += d[i][1];
                    seq.push_back(tmp);
                }
        sort(seq.begin(), seq.end());
        return unique(seq.begin(), seq.end()) != seq.end();
    }
};
