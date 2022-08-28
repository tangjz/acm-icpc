/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, Employee *> emp;
        for(auto &it: employees)
            emp[it -> id] = it;
        unordered_map<int, int> val;
        function<int(int)> calc = [&](int u) {
            if(val.count(u))
                return val[u];
            Employee *it = emp[u];
            int &ret = val[u] = it -> importance;
            for(int v: it -> subordinates)
                ret += calc(v);
            return ret;
        };
        return calc(id);
    }
};
