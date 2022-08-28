class Solution {
public:
    vector<int> memLeak(int memory1, int memory2) {
        int pos = 1;
        while(pos <= max(memory1, memory2)) {
            if(memory1 >= memory2) {
                memory1 -= pos;
            } else {
                memory2 -= pos;
            }
            pos += 1;
        }
        return {pos, memory1, memory2};
    }
};
