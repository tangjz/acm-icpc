class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int dif = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                if(colors[i] != colors[j])
                    dif = max(dif, j - i);
        return dif;
    }
};
