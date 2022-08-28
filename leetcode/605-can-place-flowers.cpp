class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int m = flowerbed.size();
        for(int i = 0; n > 0 && i < m; ) {
            if(flowerbed[i]) {
                ++i;
                continue;
            }
            int j = i++;
            for( ; i < m && !flowerbed[i]; ++i);
            int len = i - j - (i < m) - (j > 0);
            n -= (len + 1) / 2;
        }
        return n <= 0;
    }
};
