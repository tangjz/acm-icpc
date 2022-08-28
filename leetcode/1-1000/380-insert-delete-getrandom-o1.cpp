class RandomizedSet {
    mt19937 rnd;
    unordered_map<int, int> pos;
    vector<int> seq;
    int get_index(int v) {
        auto it = pos.find(v);
        return it == pos.end() ? -1 : it -> second;
    }
    void push_back(int v) {
        pos[v] = seq.size();
        seq.push_back(v);
    }
    void pop_back() {
        pos.erase(seq.back());
        seq.pop_back();
    }
    void swap_element(int i, int j) {
        swap(pos[seq[i]], pos[seq[j]]);
        swap(seq[i], seq[j]);
    }
    int random_element() {
        return seq[rnd() % seq.size()];
    }
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        rnd.seed(time(nullptr));
        unordered_map<int, int>().swap(pos);
        vector<int>().swap(seq);
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(get_index(val) != -1)
            return 0;
        push_back(val);
        return 1;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        int idx = get_index(val);
        if(idx == -1)
            return 0;
        swap_element(idx, seq.size() - 1);
        pop_back();
        return 1;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return random_element();
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
