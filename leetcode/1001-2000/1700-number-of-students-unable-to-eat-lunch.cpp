class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int cnt[2] = {};
        for(int x : students)
            ++cnt[x];
        for(int x : sandwiches) {
            if(!cnt[x])
                break;
            --cnt[x];
        }
        return cnt[0] + cnt[1];
    }
};
