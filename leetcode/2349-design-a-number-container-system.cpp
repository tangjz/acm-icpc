class NumberContainers {
    map<int, int> seq;
    map<int, set<int> > ref;
public:
    NumberContainers() {
        
    }
    
    void change(int index, int number) {
        if(seq.count(index)) {
            ref[seq[index]].erase(index);
        }
        seq[index] = number;
        ref[number].insert(index);
    }
    
    int find(int number) {
        return ref.count(number) && !ref[number].empty() ? *ref[number].begin() : -1;
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
