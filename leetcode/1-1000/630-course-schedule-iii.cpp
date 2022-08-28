class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        int sum = 0;
        priority_queue<int> que;
        sort(courses.begin(), courses.end(), [&](auto const &u, auto const &v) {
            return u[1] < v[1];
        });
        for(auto &it: courses) {
            sum += it[0];
            que.push(it[0]);
            if(sum > it[1]) {
                sum -= que.top();
                que.pop();
            }
        }
        return que.size();
    }
};
