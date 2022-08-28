class Solution {
public:
    int badSensor(vector<int>& sensor1, vector<int>& sensor2) {
        int n = sensor1.size(), pos = 0;
        for( ; pos < n && sensor1[pos] == sensor2[pos]; ++pos);
        if(pos >= n - 1)
            return -1;
        bool lft = 1, rht = 1;
        for(int i = pos + 1; i < n; ++i) {
            lft &= sensor1[i - 1] == sensor2[i];
            rht &= sensor1[i] == sensor2[i - 1];
        }
        if(lft == rht)
            return -1;
        return lft ? 1 : 2;
    }
};
