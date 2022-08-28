class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        typedef long long LL;
        LL las = 0;
        unordered_map<int, LL> tim;
        for(int x: tasks) {
            las = max(las + 1, tim[x]);
            tim[x] = las + space + 1;
        }
        return las;
    }
};
