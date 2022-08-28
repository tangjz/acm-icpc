class FirstUnique {
    queue<int> candidates;
    unordered_map<int, int> counts;
public:
    FirstUnique(vector<int>& nums) {
        queue<int>().swap(candidates);
        unordered_map<int, int>().swap(counts);
        for(int x : nums)
            add(x);
    }
    
    int showFirstUnique() {
        return candidates.empty() ? -1 : candidates.front();
    }
    
    void add(int value) {
        unordered_map<int, int>::iterator it = counts.find(value);
        if(it == counts.end()) {
            candidates.push(value);
            counts.insert(make_pair(value, 1));
        } else {
            ++(it -> second);
            while(!candidates.empty() && counts[candidates.front()] > 1)
                candidates.pop();
        }
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
